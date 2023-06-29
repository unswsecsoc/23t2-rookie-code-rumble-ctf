FROM alpine:latest

EXPOSE 9999

RUN apk add socat gcc musl-dev

WORKDIR /app

COPY ./starships ./flag ./

CMD socat TCP4-LISTEN:9999,fork EXEC:/app/starships
