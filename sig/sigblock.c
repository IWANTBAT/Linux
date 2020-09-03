#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sigblack(int signo)
{
    printf("signum is %d\n",signo);

}

int main()
{
    signal(2,sigblack);
    sigset_t set,oldset;
    sigemptyset(&set);
    sigemptyset(&oldset);
    sigfillset(&set);
    sigprocmask(SIG_BLOCK,&set,&oldset);
    while(1){
        sleep(1);
    }
    return 0;
}
