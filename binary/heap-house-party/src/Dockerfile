FROM alpine:latest

EXPOSE 9999

RUN apk add socat gcc musl-dev

WORKDIR /app

COPY ./challenge.c ./flag.txt ./

# -static so that ASLR is disabled, which also just happens to make malloc
# return the same addresses for allocations of the same size (after a free).
RUN gcc challenge.c -static

CMD socat TCP4-LISTEN:9999,fork EXEC:/app/a.out
