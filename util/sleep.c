#include "kernel/types.h"
#include "user/user.h"

int
main(int argc,char *argv[])
{
        if(argc!=2){
                printf("usage: sleep [timeout] \n");
        }else{
                int timeout = atoi(argv[1]);
                sleep(timeout);
        }
        exit(0);
}