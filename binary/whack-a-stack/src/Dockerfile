FROM alpine:latest

EXPOSE 9999

RUN apk add socat gcc musl-dev

WORKDIR /app

COPY ./challenge.c ./flag.txt ./

# -D_GNU_SOURCE for architecture-specific bits and bobs (viewing processor state).
# -static so that ASLR is disabled.
# -Og so that the compiler actually creates a 32-byte array of characters.
# -fno-stack-protector since you're supposed to perform stack manipulation.
RUN gcc challenge.c -D_GNU_SOURCE -static -Og -fno-stack-protector

CMD socat TCP4-LISTEN:9999,fork EXEC:/app/a.out
