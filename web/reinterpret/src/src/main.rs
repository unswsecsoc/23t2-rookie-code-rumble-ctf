#[macro_use]
extern crate rocket;

use rocket::response::content;

#[get("/")]
fn index() -> content::RawJson<&'static str> {
    content::RawJson("{\"api\":\"reinterpret\",\"webserver\":\"rocket\",\"routes\":[{\"path\":\"/flag\",\"method\":\"PATCH\",\"description\":\"Outputs the flag\"}]}")
}

#[patch("/flag")]
fn flag() -> content::RawJson<&'static str> {
    content::RawJson("{\"flag\":\"BEGINNER{ru5t_15_certainly_an_1nt3r3sting_langu4g3}\"}")
}

#[launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![index, flag])
}
