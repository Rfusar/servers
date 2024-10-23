/*
 LINKS 
    - https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers
    - https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP

    HEADER:
        X-Frame-Options: 
            - DENY -> non è permesso utilizzare la risorsa in un iframe html
            - SAMEORIGIN -> incorporamento consentito pero solo dallo stesso dominio
            - ALLOW-FROM uri -> specifica gli URI permessi (obsoleto e poco utilizzato)

        X-Content-Type-Options:
            - nosniff 

        Content-Security-Policy:
            -

        Strict-Transport-Security:
            - max-age=int, 
            - includeSubdomains

        Referrer-Policy:
            - noreferrer
            - strict-origin
            - same-origin

        Feature-Policy o Permissions-Policy:

*/
typedef struct {
    const char *apikey;
    const char *(*codifica)();
    const int master; // 0=master, 1=admin, -1=user
} Private;

typedef struct {
    const char *url; 
    const char *method; 
    const char *contentType;
    const char *body;
    int status;
    const Private hash;
    const char *status_text;
} Route;

char *res_OK(Route *r){ 
    char *res;
    char *b64_res = b64_encode(r->body, strlen(r->body));
    snprintf(res,
        BUFFER_SIZE,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "X-Frame-Options: DENY\r\n"
        "X-XSS-Protection: 1; mode=block\r\n"
        "\r\n"
        "%s\r\n"
        "base64: %s\r\n",
        r->status, r->status_text, r->contentType, strlen(r->body), r->body, b64_res);
    return res;
}


char *res_CRASH(){ 
    char *res = ""
        "HTTP/1.1 500 Server CRASH --- HELP\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 8\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "X-Frame-Options: DENY\r\n"
        "X-XSS-Protection: 1; mode=block\r\n"
        "\r\n"
        "AIUTO KO\r\n";
    return res;
}
