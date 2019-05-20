#include<stdio.h>

int main()
{
	int kor, eng, math,jap;
	int sum = 0;

	math = 80;
	eng = 100;
	kor = 90;	jap=50;
	sum = 80 + 100 + 90+50;

	printf("This program print report card.\n");

	printf("Korean : %d\n", kor);
	printf("English : %d\n", eng);
	printf("Math : %d\n", math);
	printf("Sum : %d\n", sum); printf("Japanese : %d\n", jap);
	printf("Average : %d\n", sum/4);
	return 0;
}
