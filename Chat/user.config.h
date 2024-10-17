#include "server.config.h"

typedef struct {
    const char *username;
    const char *password;
} User_login;

typedef struct {
    User_login credential;
    const char *IP;
} USER;

User_login users[] = {
    {"Richi", "changeit"}
};



void handle_login(int socket, const char *body){
    char username[50];
    char password[50];
    int is_authenticated = 0;
    
    sscanf(body, "username=%49[^&]&password=%49s", username, password);
    for (int i = 0; i < sizeof(users)/sizeof(User_login); i++){
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password)==0) {
            is_authenticated = 1;
            break;
        }
    }
    char res[BUFFER_SIZE];
    if(is_authenticated){
        //const char *session_token="OK";
        //time_t now = time(NULL);
        //time_t expires = 60+now;
        //char expires_str[100];
        //struct tm *tm_info = gmtime(&expires);
        //strftime(expires_str, sizeof(expires_str), "%a, %d %b %Y %H:%M:%S GMT", tm_info);

        //char cookie[256];
        //sprintf(cookie, "Set-Cookie: session_token=%s; HttpOnly; Secure; SameSite=Strict; Expires=%s\r\n", session_token, expires_str);

        char *content = HEADER_OK("text/plain", "Minchia ma sei Tu, grande");
        strncpy(res, content, sizeof(res));
    }
    else {
        snprintf(res, sizeof(res), 
              "HTTP/1.1 401 Unauthorized\r\n"
              "Content-Type: text/plain\r\n"
              "Connection: close\r\n"
              "\r\n"
              "Chi Cazzo Sei?");
    }
    send(socket, res, strlen(res), 0);
}
