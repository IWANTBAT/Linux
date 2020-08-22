#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>
#include<stdlib.h>
char g_command[1024];

int GetCommand(){
    //字符数组清空
    memset(g_command,'\0',sizeof(g_command));

    printf("[@wxw minishell]$");
    if(fgets(g_command,sizeof(g_command)-1,stdin) == NULL)
    {
        printf("读取错误\n");
        return -1;
    }
    return 0;
}

int ExecCommand(char* argv[]){
    if(argv[0] == NULL){
        printf("ExecCommand 错误\n");
        return -1;
    }

    pid_t pid = fork();
    if(pid<0){
        printf("创建子进程失败\n");
        return -1;
    }
    else if(pid == 0){
        //child
        execvp(argv[0],argv);
        //
        exit(0);
    }
    else{
        //father
        waitpid(pid,NULL,0);
    }
}
int DealCommand(char* command){
    //差错控制
    if(!command || *command == '\0')
    {
        printf("command 错误\n");
        return -1;
    }

    //拆分命令
    int argc = 0;
    char* argv[1024] = {0};

    while(*command){
        while(!isspace(*command) && *command !='\0'){
            argv[argc] = command;
            argc++;
            while(!isspace(*command) && *command != '\0'){
                command++;
            }
            *command = '\0';
        }
        command++;
    }
    argv[argc] = NULL;

    ExecCommand(argv);

    return 0;
}
int main()
{
    while(1)
    {
        //从标准输入读取命令
        if(GetCommand() == -1){
            continue;
        }

        //拆分字符串，创建子进程，子进程程序替换
        DealCommand(g_command);

    }
    return 0;
}
