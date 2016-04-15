#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void intervalsort(int *pt, int x)
{
	int i, tmp;

	for (i = 1; i <= x; i++){
		if (*pt > *(pt + i)){
			tmp = *pt;
			*pt = *(pt + i);
			*(pt + i) = tmp;
		}
	}


}

int main()
{
	int SIZE;

	printf("�� ĭ ���ǰǰ���? : ");
	scanf("%d", &SIZE);

	int i, j, x = SIZE;
	int *a = (int *)malloc(sizeof(int) * SIZE);

	printf("��Ҹ� �Է��ϼ���. : ");
	for (i = 0; i < SIZE; i++)
		scanf("%d", a + i);

	while (x > 1){
		x/= 2;
		for (i = 0; i + x < SIZE; i++){
			intervalsort(a + i, x);
		}

		printf("interval %d : ", x);
		for (i = 0; i < SIZE; i++)
			printf("%d ", *(a + i));
		printf("\n");
	} 

	printf("\nRESULT : ");
	for (i = 0; i < SIZE; i++)
		printf("%d ", *(a + i));
	printf("\n");

	free(a);
	system("pause");
	return 0;
}