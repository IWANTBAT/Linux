#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

char g_command[1024];

int Getcommand(){
  //字符数组清空
  memset(g_command,'\0',sizeof(g_command));
  
  printf("[test@localhost minishell]$ ");
  fflush(stdout);
  if(fgets(g_command,sizeof(g_command)-1,stdin) == NULL){
    
    printf("fgets error\n");
    return -1;
  }
  return 0;
}

int Execlcommand(char* argv[]){
  if(argv[0] == NULL){
    printf("Execlcommand error\n");
    return -1;
  }
  pid_t pid = fork();
  if(pid<0){
    printf("create pid false\n");
    return -1;
  }
  else if(pid == 0){
    //child
    //进程程序替换
    execvp(argv[0],argv);
    //如果替换失败了，就要杀掉子进程
    exit(0);
  }
  else{
    //father
    waitpid(pid,NULL,0);
  }
  return 0;
}

int Docommand(char* command){
  if(!command || *command == '\0'){
    printf("command error\n");
    return -1;
  }

  //拆分命令
  int argc = 0;
  char* argv1[1024] = {0};

  while(*command){
    while(!isspace(*command) && *command != '\0'){
      argv1[argc] = command;
      argc++;
      while(!isspace(*command) && *command != '\0'){
        command++;
      }
      *command = '\0';
    }
    command++;
  }
  argv1[argc] = NULL;//命令行参数必须以NULL结尾

  //创建子进程进行程序替换
  Execlcommand(argv1);
  return 0;
}
int main()
{
  while(1){
  //从标准输入中读取命令
  while(Getcommand() == -1)
    continue;
  //拆分字符串，创建子进程，进程程序替换
  Docommand(g_command);
  }
  return 0;
}
