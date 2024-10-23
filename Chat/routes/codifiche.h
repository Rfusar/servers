#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char *b64_encode(const unsigned char *input, int length){
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    BUF_MEM *bptr;

    b64 = BIO_push(b64, bmem);

    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length+1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = '\0';

    BIO_free(b64);
    return buff;
}
