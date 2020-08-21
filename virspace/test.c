#include<stdio.h>
#include<unistd.h>

int main()
{
    int aa = 10;
    int pid = fork();
    if(pid<0){
        perror("fork");
        return 0;
    }
    else if(pid>0){
        //father
        aa += 10;
        printf("father aa = %d,%p\n",aa,&aa);
    }
    else{
        //child
        aa += 30;
        printf("child aa = %d,%p\n",aa,&aa);
    }
    printf("%d\n",aa);
    return 0;
}
