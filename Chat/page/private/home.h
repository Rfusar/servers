void handle_home(int socket, const char *headers){
    const char *cookieName = "session_token=";
    char *cookieValue = NULL;
    char *cookieStart = strstr(headers, cookieName);
    if(cookieStart){
        cookieStart += strlen(cookieName);
        char *cookieEnd = strchr(cookieStart, ';');
        if (cookieEnd){
            size_t cookieLen = cookieEnd-cookieStart;
            cookieValue = (char *)malloc(cookieLen+1);
            strncpy(cookieValue, cookieStart, cookieLen);
            cookieValue[cookieLen] = '\0';
        }
        else{
            cookieValue = strdup(cookieStart);
        }
    }
    if (cookieValue && strcmp(cookieValue, "OK")==0){
        const char *res = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/plain\r\n"
                          "Connection: close\r\n\r\n"
                          "Ciao caro!";
        send(socket, res, strlen(res), 0);
    }
    else{
        const char *res = "HTTP/1.1 401 Unauthorized\r\n"
                          "Content-Type: text/plain\r\n"
                          "Connection: close \r\n\r\n"
                          "Vaffanculo";
        send(socket, res, strlen(res), 0);
    }
    free(cookieValue);
    close(socket);
}
