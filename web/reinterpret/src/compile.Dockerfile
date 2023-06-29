FROM rust:alpine

EXPOSE 80

RUN apk add musl-dev pkgconfig openssl openssl-dev python3 nginx
WORKDIR /
RUN USER=root cargo new app
WORKDIR /app

COPY ./Cargo.lock ./Cargo.toml ./
RUN cargo build --release

COPY ./src ./src/
RUN touch src/main.rs && \
    cargo build --release
