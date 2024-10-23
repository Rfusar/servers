FROM gcc:latest
WORKDIR /usr/src/app
COPY server.c .
RUN gcc -o server server.c
EXPOSE 8000
CMD ["./server"]
