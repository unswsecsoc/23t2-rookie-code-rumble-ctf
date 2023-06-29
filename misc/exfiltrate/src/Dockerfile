FROM python:3-alpine

EXPOSE 1337

RUN apk add socat

WORKDIR /app

COPY ./challenge.py ./run.sh ./

CMD socat TCP4-LISTEN:1337,fork EXEC:./run.sh
