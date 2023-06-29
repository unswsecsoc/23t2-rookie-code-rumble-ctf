FROM rustlang/rust:nightly-alpine

RUN apk add musl-dev

WORKDIR /
RUN USER=root cargo new app
WORKDIR /app

COPY ./Cargo.toml ./Cargo.lock ./
RUN cargo build --release

COPY ./src ./src/
RUN touch src/main.rs && \
    cargo build --release

