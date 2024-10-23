#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

// Custom
#define len(arr) (sizeof(arr)/sizeof(arr[0]))

#include "server.config.const.h"
#include "routes/codifiche.h"
#include "server.config.init.h"


#include "routes/response.h"

#include "DB.h"
#include "server.config.base.h"
//#include "tls.h"

