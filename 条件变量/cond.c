#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define THREADCOUNT 2

//有面为1，无面为0
int g_nodel = 0;

//互斥锁

pthread_mutex_t g_mutex;

//条件变量
pthread_cond_t g_eat;
pthread_cond_t g_make;

//吃面线程入口函数
void* Eat_start(void* arg){
  (void)arg;

  //只要有面就一直吃面
  while(1){
    //加锁
    pthread_mutex_lock(&g_mutex);

    //要循环判断是否有面
    while(g_nodel == 0){
      //有面吃面的执行流调用等待接口
      pthread_cond_wait(&g_eat,&g_mutex);
    }
    //退出等待说明有面
    g_nodel--;
    printf("eat nondel %d\n",g_nodel);
    //吃完解锁
    pthread_mutex_unlock(&g_mutex);
    
    //没面了通知做面的执行流来做面
    pthread_cond_signal(&g_make);
  }
  return NULL;
}

//做面线程的入口函数
void* Make_start(void* arg){
  (void)arg;

  //只要没有面一致做面
  while(1){
    pthread_mutex_lock(&g_mutex);

    while(g_nodel == 1){

      pthread_cond_wait(&g_make,&g_mutex);
    }
    g_nodel++;
    printf("make nondel %d\n",g_nodel);
    pthread_mutex_unlock(&g_mutex);

    //通知吃面的执行流来吃面
    pthread_cond_signal(&g_eat);
  }
  return NULL;
}

int main()
{
  //初始化互斥锁
  pthread_mutex_init(&g_mutex,NULL);
  //初始化条件变量
  pthread_cond_init(&g_eat,NULL);
  pthread_cond_init(&g_eat,NULL);

  //创建吃面和做面的线程
  pthread_t eat_tid[THREADCOUNT],make_tid[THREADCOUNT];

  int i = 0;
  for(;i<THREADCOUNT;i++){
    int ret = pthread_create(&eat_tid[i],NULL,Eat_start,NULL);
    if(ret<0){
      perror("pthread_create");
      return 0;
    }

    ret = pthread_create(&make_tid[i],NULL,Make_start,NULL);
    if(ret<0){
      perror("pthread_create");
      return 0;
    }
    for(i = 0;i<THREADCOUNT;i++){
      pthread_join(eat_tid[i],NULL);
      pthread_join(make_tid[i],NULL);
    }
  }


  return 0;
}
