#include "allnet.h"

void *thread_func(void *arg)
{ 
    pthread_detach(pthread_self());
    server_work((int)arg);
}