#![feature(io_error_more)]

use std::env;

use actix_multipart::{form::{MultipartForm, tempfile::{TempFile, TempFileConfig}}};
use actix_web::{get, post, web, error, Error, App, Responder, HttpServer, HttpResponse};
use rand::{thread_rng, distributions::Alphanumeric, Rng};

#[derive(MultipartForm)]
struct Upload {
    file: TempFile
}

#[post("/")]
async fn save(form: MultipartForm<Upload>) -> Result<impl Responder, Error> {
    if form.file.size < 1 || form.file.size > 10240 {
        Err(error::ErrorBadRequest("file size must be [1, 10240] bytes"))
    }

    else {
        let mut rng = thread_rng();
        let name = (0..64).map(|_| rng.sample(Alphanumeric) as char).collect::<String>();
        let filepath = format!("./files/{}", name);
        let webpath = format!("/read/{}", name);

        form.into_inner().file.file.persist(filepath).unwrap();
        Ok(HttpResponse::Ok().body(webpath))
    }
}

#[get("/read/{name}")]
async fn open(path: web::Path<String>) -> Result<impl Responder, Error> {
    let path = format!("./files/{}", path.into_inner());

    match std::fs::read(&path) {
        Ok(data) => Ok(HttpResponse::Ok().body(data)),

        Err(err) if err.kind() == std::io::ErrorKind::IsADirectory => {
            let response = std::fs::read_dir(&path)?
                .filter_map(|entry| entry.ok())
                .filter_map(|entry| entry.file_name().into_string().ok())
                .collect::<Vec<_>>()
                .join("\n");

            Err(error::ErrorImATeapot(response))
        },

        Err(err) => Err(error::ErrorBadRequest(err))
    }
}

#[get("/")]
async fn hello() -> impl Responder {
    let html = r#"
        <head>
            <title>Astral</title>
            <meta charset="UTF-8">
            <style>
                body {
                    position: absolute;
                    top: 50%;
                    left: 50%;
                    transform: translate(-50%, -50%);
                }
            </style>
        </head>
        <body>
            <center>
                <h1>Astral</h1>
                <p>A 🚀 memory safe 🚀, 🚀 blazing(🔥) fast 🚀 and 🚀 secure(🔒) 🚀 intergalactic file distribution network.</p>
                <form target="/" method="post" enctype="multipart/form-data">
                    <input type="file" name="file"/>
                    <button type="submit">Submit</button>
                </form>
            </center>
        </body>
    "#;

    HttpResponse::Ok().body(html)
}

#[tokio::main]
async fn main() {
    std::fs::create_dir_all("./files").unwrap();

    let app = || {
        App::new()
        .service(hello)
        .service(open)
        .service(save)
        .app_data(TempFileConfig::default().directory("./files"))
    };

    let server = HttpServer::new(app);
    let args = env::args().collect::<Vec<String>>();
    let port = args[1].parse::<u16>().unwrap();
    server.bind(("0.0.0.0", port)).unwrap().run().await.unwrap()
}
