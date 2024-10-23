void exit_program(char *testo){
    perror(testo);
    exit(EXIT_FAILURE);
}
void handle_sigint(int sig) {exit_program("\nServer off. Addios\n");}


typedef struct {
    int server_fd;
    const int opt;
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
    const User_login credential;
    const char *IP;
} USER;
typedef struct {
    int socket_fd;
    //SSL *ssl;
    const char buffer[BUFFER_SIZE];
    const USER webclient;
} Client;
