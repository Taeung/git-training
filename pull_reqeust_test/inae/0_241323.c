
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int day = 0;
	int 항공권가격 = 0;
	int 호텔_1박_가격 = 0;
	int 하루에_필요한_용돈 = 0;
	int result = 0;

	
	printf("여행은 몇박인가요? :");
	scanf("%d", &day);

	printf("항공권 가격:");
	scanf("%d", &항공권가격);

	printf("호텔1박가격:");
	scanf("%d", &호텔_1박_가격);

	printf("하루에 필요한 용돈 :");
	scanf("%d", &하루에_필요한_용돈);

	printf("============================\n");
	result = 항공권가격 + 호텔_1박_가격 * day + (day + 1) * 하루에_필요한_용돈;
	printf("총 여행 비용= %d \n", result);
	printf("============================");

	return 0;
	
}