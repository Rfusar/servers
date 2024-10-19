#include "Chat/init.h"



int main() {
    signal(SIGINT, handle_sigint);
    Server s;
    s.addrlen = sizeof(s.address);
    run(&s);
    close(s.server_fd);
    return 0;
}
