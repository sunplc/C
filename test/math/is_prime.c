#include <stdio.h>

int main()
{
	int i;
	for(i=100; i<=200; i++){
		if(is_prime(i)){
			printf("%d\n",i);
		}
	}
}

//判断是否素数
int is_prime(int a)
{
	if(a<1){
		return 0;	
	}else if(a==1 || a==2){
		return 1;
	}else{
		int i,flag=1;
		for(i=2; i<a; i++){
			if(a%i==0)
				flag = 0;
		}
		return flag;
	}
}
