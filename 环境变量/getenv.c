#include<stdio.h>
#include<unistd.h>

//三种方式获取环境变量

////1.main函数的参数获取环境变量的值
//int main(int argc,char* argv[],char* env[])
//{
//    //argc：命令行参数个数
//    //argv：命令行参数具体的内容
//    //env：环境变量
//    int i = 0;
//    for(i = 0;i<argc;i++){
//        printf("%s\n",argv[i]);
//    }
//    i = 0;
//    for(;env[i];i++){
//        printf("%s\n",env[i]);
//    }
//    return 0;
//}

//2.libc库当中提供的变量来获取

//int main()
//{
//    //libc库当中的
//    extern char** environ;
//    int i = 0;
//    for(;environ[i];i++){
//        printf("%s\n",environ[i]);
//    }
//    return 0;
//}


//3.libc库当中提供的函数获取某一个具体的环境变量的值
//char* getenv(const char* name)
// name:环境变量的名称
// 返回值：具体环境变量对应的值

#include<stdlib.h>
int main()
{
    char* PATH = getenv("PATH");
    printf("%s\n",PATH);
    return 0;
}













