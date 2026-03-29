#include <stdio.h>
#include <assert.h>

int sum(int x);


int main(void)
{
	assert(sum(1) == 1);
	assert(sum(2) == 3);
	assert(sum(3) == 6);
	assert(sum(4) == 10);
	assert(sum(5) == 15);
	assert(sum(20) == 210);
	assert(sum(0) == 0);
	assert(sum(-1) == 0);
		return 0;
}
	int sum(int x)
	{
		int resultat = 0;
		if (x > 0)
		{
			printf("sum(%d) anropas\n", x);
			resultat = x + sum(x - 1);

			printf("sum(%d) returnerar(%d)\n", x, resultat);
		}

		return resultat;
	}