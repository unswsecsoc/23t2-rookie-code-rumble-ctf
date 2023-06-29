FROM alpine

EXPOSE 9999

RUN apk add musl-dev

WORKDIR /app

COPY ./flag.txt /ctf/secret/confidental/
COPY ./dist/astral ./

CMD ./astral 9999
