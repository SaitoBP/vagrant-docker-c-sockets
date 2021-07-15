FROM gcc:latest

COPY . /usr/src/server

WORKDIR /usr/src/server

EXPOSE 80

# Compile the server.c
RUN gcc server.c -o ./build/server

CMD ["./build/server"]