

int route_requests(const char *route, const char *method, int new_conn, char *buffer){
    int is_correct_route = 1;

    if (strcmp(method, "GET")==0){
        for(char i = 0; i<len(ROUTES_GET); i++){
            if(strcmp(route, ROUTES_GET[i][0])==0){
                is_correct_route = 0;
                //Init route
                Route obj_route = {
                    .url = route,
                    .method = method,
                    .status = 200,
                    .contentType = ROUTES_GET[i][1],
                    .status_text = "OK",
                    .body=ROUTES_GET[i][2]
                };
                char *res = res_OK(&obj_route);
                send(new_conn, res, strlen(res), 0);
                return 0;;
            }
        }
    }
    if(is_correct_route==1){
        char *res_ko = res_CRASH();
        send(new_conn, res_ko, strlen(res_ko), 0);
        return 1;
    }
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
    //Gestore metodi
    for(char i=0; i<len(METHODS); i++){
        const char *current_method = METHODS[i];
        if (strcmp(method, current_method)==0){
            route_requests(route, method, new_conn, buffer);
        }
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


