#include <stdio.h>

int main(){

    char player1[30]={0};
    char player2[30]={0};
    int year1=0;
    int year2=0;

    printf("Player #1, please input your name: ");
    scanf("%s",player1);
    printf("Input your birth year: ");
    scanf("%d",&year1);

    printf("Player #2, please input your name: ");
    scanf("%s",player2);
    printf("Input your birth year: ");
    scanf("%d",&year2);

    if(year1>year2) printf("%s is younger than %s.\n",player1,player2);
    else if(year1<year2) printf("%s is younger than %s.\n",player2,player1);
    else if(year1==year2) printf("%s and %s are same age.\n",player1,player2);

    return 0;
}