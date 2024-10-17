#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <signal.h>
#include <time.h>


#define PORT 8000
#define BUFFER_SIZE 5000

#include "component.h"
#include "user.config.h"
#include "tls.h"
#include "page/init.h"
