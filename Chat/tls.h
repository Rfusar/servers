void initOpenSSL(){
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openSSL(){ EVP_cleanup(); }

SSL_CTX *createContext(){
    const SSL_METHOD *method = SSLv23_server_method();
    SSL_CTX *ctx = SSL_CTX_new(method);
    if (!ctx){
        perror("Contesto non creato, sorry :'(");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);

    }
    return ctx;
}

//Gestione Certificati
int verify_callback(int preverify_ok, X509_STORE_CTX *x509_ctx) {
    if (!preverify_ok) {
        int error = X509_STORE_CTX_get_error(x509_ctx);
        printf("Errore nella verifica del certificato: %s\n", X509_verify_cert_error_string(error));
    }
    else{
        X509 *cert = X509_STORE_CTX_get_current_cert(x509_ctx);

        ASN1_TIME *not_before = X509_get_notBefore(cert);
        ASN1_TIME *not_after = X509_get_notAfter(cert);

        time_t current_time;
        time(&current_time);

        int not_before_cmp = X509_cmp_time(not_before, &current_time);
        int not_after_cmp = X509_cmp_time(not_after, &current_time);

        if (not_before_cmp > 0 || not_after_cmp < 0){
            printf("Il certigficato è scaduto! sorry :'(");
            return 0;
        }
    }
    return preverify_ok;
}

void configure_context(SSL_CTX *ctx){
    if(SSL_CTX_use_certificate_file(ctx, "Chat/certs/server.crt", SSL_FILETYPE_PEM) <=0 ){
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if(SSL_CTX_use_PrivateKey_file(ctx, "Chat/certs/server.key", SSL_FILETYPE_PEM)<=0){
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_load_verify_locations(ctx, "Chat/certs/MASTER.crt", NULL) <= 0){
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, verify_callback);
    SSL_CTX_set_verify_depth(ctx, 4);
}
