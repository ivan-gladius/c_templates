#include <stdio.h>
#include <pthread.h>


pthread_mutex_t m1, m2;
pthread_cond_t condi;
int count = 0;


void *first( void *a)
{
	pthread_mutex_lock(&m1);

	for ( int x = 0; x < 10; x++)
	{
		printf("count: %d\tID: %d\n", count, pthread_self());
		count++;
	}

	pthread_cond_signal(&condi);

	pthread_mutex_unlock(&m1);

	pthread_exit(NULL);
}	
void *second( void *a)
{
	pthread_mutex_lock(&m2);

	pthread_cond_wait(&condi, &m2);

	for ( int x = 0; x < 10; x++)
	{
		printf("count: %d\tID: %d\n", count, pthread_self());
		count++;
	}


	pthread_mutex_unlock(&m2);

	pthread_exit(NULL);
}	



int main()
{
	pthread_t t1, t2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_cond_init(&condi, NULL);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&t1, &attr, first, NULL);
	pthread_create(&t2, &attr, second, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	pthread_cond_destroy(&condi);

	pthread_exit(NULL);

}	

