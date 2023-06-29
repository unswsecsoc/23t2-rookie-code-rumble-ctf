FROM alpine:latest

EXPOSE 9999

RUN apk add socat gcc musl-dev

WORKDIR /app

COPY ./challenge.c ./flag.txt ./

RUN gcc challenge.c

CMD socat TCP4-LISTEN:9999,fork EXEC:/app/a.out
