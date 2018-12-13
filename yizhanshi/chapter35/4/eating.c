// 别人的代码 http://blog.csdn.net/wynter_/article/details/52585611

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

pthread_mutex_t chopstick[6];

void *eat_think(void *arg)
{
	char phi = *(char*)arg;
	int left, right;
	//int i = 0;

	switch(phi)
	{
		case 'A':
			left = 5;
			right = 1;
			break;
		case 'B':
			left = 1;
			right = 2;
			break;
		case 'C':
			left = 2;
			right = 3;
			break;
		case 'D':
			left = 3;
			right = 4;
			break;
		case 'E':
			left = 4;
			right = 5;
			break;
		default:
			break;
	}

	while(1)
	{
		sleep(2);  //思考
		pthread_mutex_lock(&chopstick[left]);  //拿起左边的筷子
		printf("Phi %c fetches chopstick %d\n", phi, left);
		if(pthread_mutex_trylock(&chopstick[right]) == EBUSY)  //拿起右边的筷子
		{
			pthread_mutex_unlock(&chopstick[left]);  //如果右边的筷子被拿走则放下左边的筷子
			continue;
		}

		//pthread_mutex_lock(&chopstick[right]);   //如果要观察死锁，则将上一句if注释，再将该行注释取消
		printf("Phi %c fetch chopstick %d\n", phi, right);
		printf("Phi %c is eating...\n", phi);
		sleep(2);  //吃饭

		pthread_mutex_unlock(&chopstick[left]);  //放下左边的筷子
		printf("Phi %c release the chopstick %d\n", phi, left);
		pthread_mutex_unlock(&chopstick[right]);  //放下右边的筷子
		printf("Phi %c release the chopstick %d\n", phi, right);
	}
}

int main()
{
	pthread_t A, B, C, D, E;  //五位哲学家

	int i = 0;
	for(i = 0; i < 5; ++i)
	{
		pthread_mutex_init(&chopstick[i], NULL);
	}

	pthread_create(&A, NULL, eat_think, "A");
	pthread_create(&B, NULL, eat_think, "B");
	pthread_create(&C, NULL, eat_think, "C");
	pthread_create(&D, NULL, eat_think, "D");
	pthread_create(&E, NULL, eat_think, "E");

	pthread_join(A, NULL);
	pthread_join(B, NULL);
	pthread_join(C, NULL);
	pthread_join(D, NULL);
	pthread_join(E, NULL);

	return 0;
}
