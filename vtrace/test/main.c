#include <stdio.h>

extern void moin(void);

void lol()
{
	printf("lol\n");
}

void rofl()
{
	printf("rofl\n");
	lol();
}

void main()
{
	printf("main\n");

	lol();
	rofl();
	rofl();
	lol();

	moin();
}
