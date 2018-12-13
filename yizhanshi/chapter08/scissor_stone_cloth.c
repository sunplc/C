#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	char gesture[3][10] = { "scissor", "stone", "cloth" };
	int man, computer, ret, result;
	srand(time(NULL));
	while (1) {
		computer = rand() % 3;
		printf("\nplease input your gesture (0->scissor 1->stone 2->cloth):\n");
		ret = scanf("%d", &man);
		if (ret != 1 || man < 0 || man > 2) {
			printf("Invalid input! Please input 0, 1 or 2.\n");
			continue;
		}
		printf("Your gesture: %s\tComputer's gesture: %s\n",
				gesture[man], gesture[computer]);
		result = (man - computer + 4) % 3 - 1;
		if (result > 0)
			printf("You win!\n");
		else if (result == 0)
			printf("Draw!\n");
		else
			printf("You lose!\n");
	}
	return 0;
}
