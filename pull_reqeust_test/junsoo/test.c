#include<stdio.h>
int main()
{
	char name[3][10] = { 0, };
	int score[3][6] = { 67, };

	for (int i = 0; i < 3;i++)
	{
		printf("이름과 국어, 영어, 수학성적을 입력하시오 : ");
		scanf("%s %d %d %d", name[i], &score[i][0], &score[i][2], &score[i][4]);
		fflush(stdin);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 6; j = j + 2)
		{
			score[i][j] = 'C';
			if ((score[i][j - 1] >= score[1][j - 1]) && i != 1)
			{
				score[i][j]--;
			}
			if ((score[i][j - 1] >= score[0][j - 1]) && i != 0)
			{
				score[i][j]--;
			}
			if ((score[i][j - 1] >= score[2][j - 1]) && i != 2)
			{
				score[i][j]--;
			}
		}
	}
	printf("\n성적 처리 결과 \n");
	printf("	국어   영어  수학  합(평균)\n");
	for (int i = 0; i < 3;i++)
	{
		printf("%s %d (%c) %d (%c) %d (%c) %d(%0.f)\n", name[i], score[i][0], score[i][1], score[i][2], score[i][3], score[i][4], score[i][5], score[i][0]+ score[i][2]+ score[i][4],(double)(score[i][0] + score[i][2] + score[i][4])/3);
	}
	printf("------------------------------------------------\n");
	printf("합(평균) %d (%.0f) %d (%.0f) %d (%.0f) %d (%.0f)", score[0][0] + score[1][0] + score[2][0],(double)(score[0][0] + score[1][0] + score[2][0])/3, (score[0][2] + score[1][2] + score[2][2]) , (double)(score[0][2] + score[1][2] + score[2][2]) / 3, score[0][4] + score[1][4] + score[2][4], (double)(score[0][4] + score[1][4] + score[2][4]) / 3, score[0][0] + score[1][0] + score[2][0]+ score[0][2] + score[1][2] + score[2][2]+ score[0][4] + score[1][4] + score[2][4],(double)(score[0][0] + score[1][0] + score[2][0] + score[0][2] + score[1][2] + score[2][2] + score[0][4] + score[1][4] + score[2][4]) / 3);
	printf("\n");

	return 0;
}