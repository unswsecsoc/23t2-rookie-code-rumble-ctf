FROM python:3-alpine

EXPOSE 9999

RUN apk add socat

WORKDIR /app

COPY ./challenge.py ./

CMD socat TCP4-LISTEN:9999,fork EXEC:"python challenge.py"
