#include <stdio.h>

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
}
