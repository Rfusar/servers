void route_requests(const char *route, int new_conn, char *buffer){
    char *res;
    if(strcmp(route, "/home")==0){ 
        Connect_to_DB();
        const char *KEY = "ChiaveSegreta: ";
        char *content_length_header = strstr(buffer, KEY);
        if (content_length_header) {
            int content_length = atoi(content_length_header + strlen(KEY));
            printf("ChiaveSegreta trovato: %d\n", content_length);
            res = HEADER_OK("200 OK", "text/plain", "HOME");
        } 
        else { 
            res = HEADER_OK("401 Unauthorized", "text/plain", "noGood");
        }
    }
    else if(strcmp(route, "/")==0){ res = HEADER_OK("200", "text/plain", "Default");} 
    send(new_conn, res, strlen(res), 0);
}

void handle_client(int new_conn){
    char buffer[BUFFER_SIZE] = {0};

    int valread = read(new_conn, buffer, sizeof(buffer)-1);
    buffer[valread] = '\0';

    printf("Buffer: %s", buffer);

    char method[8], route[256];
    sscanf(buffer, "%s %s", method, route);

    char *endHeader = strstr(buffer, "\r\n\r\n");
    if(endHeader!=NULL){
        *endHeader = '\0';
        endHeader+=4;
        char *body=endHeader;
    }
    

    if(strcmp(method, "GET")==0){
        route_requests(route, new_conn, buffer);
    }
    close(new_conn);
}

void run(Server *s){
    s->server_fd = socket(AF_INET, SOCK_STREAM, 0);

    //Error socket
    if (s->server_fd == 0){
        exit_program("Errore creazione del socket");
    }

    //Config
    s->address.sin_family = AF_INET;
    s->address.sin_addr.s_addr = inet_addr(indirizzo);
    s->address.sin_port = htons(PORT);

    //Error Bind
    if(bind(s->server_fd, (struct sockaddr *)&s->address, sizeof(s->address))<0){
        exit_program("Errore binding");
    }

    //Error start
    if (listen(s->server_fd, 3)<0){
        exit_program("Errore nell'ascolto");
    }
    printf("Server in ascolto sulla porta %d\n", PORT);
    while (1) {
        int new_conn = accept(s->server_fd, (struct sockaddr *)&s->address, (socklen_t *)&s->addrlen);
        if (new_conn < 0) {
            exit_program("Errore nell'accettazione della connessione");
        }
        handle_client(new_conn);
    }
}


