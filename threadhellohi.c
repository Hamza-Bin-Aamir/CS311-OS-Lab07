#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void* thread1(void *arg)
{
	printf("Hello!!\n");
	return NULL;
}

void* thread2(void *arg)
{
    printf("How are you?\n");
	return NULL;
}
int main()
{
    int status;
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}