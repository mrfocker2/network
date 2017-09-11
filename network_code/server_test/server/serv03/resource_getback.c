#include "allnet.h"

void resource_getback(int signo)
{
    while(waitpid(-1, 0, WNOHANG) > 0) ; //while to getback resource
}