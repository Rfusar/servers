#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/crypto.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>


void exit_program(char *testo){
    perror(testo);
    exit(EXIT_FAILURE);
}
void handle_sigint(int sig) {exit_program("\nServer off. Addios\n");}

#define PORT 8000
#define BUFFER_SIZE 5000
#define indirizzo "127.0.0.1"

typedef struct {
    int server_fd;
    int opt;
    struct sockaddr_in address;
    int addrlen;
    //SSL_CTX *ssl_ctx;
} Server;

//Client
typedef struct {
    const char *username;
    const char *password;
} User_login;
typedef struct {
    User_login credential;
    const char *IP;
} USER;
typedef struct {
    int socket_fd;
    SSL *ssl;
    char buffer[BUFFER_SIZE];
    USER webclient;
} Client;

#include "component.h"
#include "DB.h"
#include "server.config.base.h"
//#include "tls.h"
#include "page/init.h"
