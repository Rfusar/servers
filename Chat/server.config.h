typedef struct {
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int addrlen;
    int opt;
    char message[BUFFER_SIZE];
} Server;



void handle_sigint(int sig) {
    printf("\nServer off. Addios\n");
    exit(EXIT_SUCCESS);
}

void CreateSocket(Server* s) {
    if ((s->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Non sono riuscito a creare il socket");
        exit(EXIT_FAILURE);
    }
}

void SetSockOpt(Server* s) {
    s->opt = 1;
    if (setsockopt(s->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &s->opt, sizeof(s->opt))) {
        perror("Errore nel setsockopt");
        close(s->server_fd);
        exit(EXIT_FAILURE);
    }
}

void ConfigDefault(Server* s) {
    s->addrlen = sizeof(s->address);
    s->address.sin_family = AF_INET;
    s->address.sin_addr.s_addr = INADDR_ANY;
    s->address.sin_port = htons(PORT);
}

void Bind(Server* s) {
    if (bind(s->server_fd, (struct sockaddr *)&s->address, sizeof(s->address)) < 0) {
        perror("Errore nel binding");
        close(s->server_fd);
        exit(EXIT_FAILURE);
    }
}

void Run(Server* s) {
    if (listen(s->server_fd, 3) < 0) {
        perror("Errore nell'ascolto");
        close(s->server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server in ascolto sulla porta %d...\n", PORT);
}
