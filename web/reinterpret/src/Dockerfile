FROM alpine

EXPOSE 80

RUN apk add musl-dev pkgconfig openssl openssl-dev python3 nginx
WORKDIR /app

COPY ./dist/reinterpret ./Rocket.toml ./

# nginx
COPY ./nginx.conf /etc/nginx/http.d/default.conf
COPY ./custom_pages /custom_pages

CMD nginx && ./reinterpret
