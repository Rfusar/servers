#define PORT 8000
#define BUFFER_SIZE (1024 * 10)
#define indirizzo "127.0.0.1"
#define METHODS (const char *[]){ \
    "GET", "POST" \
}

#define HEADER_DEFAULT { \
    /**/ \
}

#define ROUTES_GET (const char *[][3]) { \
    {"/", "text/html", "<h1>Home Page</h1>"} \
    {"/r0", "text/html", "<h1>Home r0</h1>"} \
    {"/r1", "text/html", "<h1>Home r1</h1>"} \
    {"/r2", "text/html", "<h1>Home r2</h1>"} \
}

#define ROUTES_POST (const char *[][2]){ \
    {"/home", "application/json", "{\"res\": \"Home Page\"}"} \
}

