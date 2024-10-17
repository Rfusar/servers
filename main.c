#include "Chat/init.h"

void INIT_SERVER(Server *s){
    CreateSocket(s);
    SetSockOpt(s);
    ConfigDefault(s);
    Bind(s);
    Run(s);
}


int main() {
    signal(SIGINT, handle_sigint); // Gestione del segnale SIGINT

    Server server;
    int sock;
    SSL_CTX *ctx;

    initOpenSSL();
    ctx = createContext();
    configure_context(ctx);
    INIT_SERVER(&server);


    while (1) {
        server.new_socket = accept(server.server_fd, (struct sockaddr *)&server.address, (socklen_t*)&server.addrlen);
        if (server.new_socket < 0) {
            perror("Errore nell'accettazione della connessione");
            continue;
        }

        SSL *ssl = SSL_new(ctx);
        if(!ssl){
            ERR_print_errors_fp(stderr);
            close(server.new_socket);
            continue;
        }
        SSL_set_fd(ssl, server.new_socket);
        if (SSL_accept(ssl) <= 0){
            ERR_print_errors_fp(stderr);
            close(server.new_socket);
            continue;
        }

        char *client_ip = inet_ntoa(server.address.sin_addr);
        printf("Connessione VISTA : %s", client_ip);
        
        int bytes_read = SSL_read(ssl, server.message, BUFFER_SIZE-1);
        if (bytes_read <= 0) {
            int ssl_err = SSL_get_error(ssl, bytes_read);
            fprintf(stderr, "Errore in SSL_read: %d\n", ssl_err);
            SSL_shutdown(ssl);
            SSL_free(ssl);
            close(server.new_socket);
            continue;
        }
        char *endHeader = strstr(server.message, "\r\n\r\n");
        if (endHeader != NULL){
            *endHeader = '\0';
            char *header = server.message;
            char *body = endHeader+4;

            char *response_template = "HTTPCaioooooo";//HEADER_OK("text/plain", "Grande Fra! :)");
            SSL_write(ssl, response_template, strlen(response_template));
        }
        else{
            perror("Richiesta non valida");
            SSL_shutdown(ssl);
            SSL_free(ssl);
            close(server.new_socket);
            continue;
        }
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(server.new_socket);
    }
    close(server.server_fd);
    SSL_CTX_free(ctx);
    cleanup_openSSL();
    return 0;
}
