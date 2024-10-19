char *HEADER_OK(const char *status, const char *contentType, const char *content){ 
    
    static char res[BUFFER_SIZE];
    snprintf(res,
        BUFFER_SIZE,

        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "X-Frame-Options: DENY\r\n"
        "X-XSS-Protection: 1; mode=block\r\n"
        "\r\n"
        "%s\r\n",
        
        status, contentType, strlen(content), content);
    
    return res;
}
