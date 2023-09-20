#include <stdio.h>

int main() {
    double num1, num2;
    double sum, diff, prod, quot;

    // 사용자로부터 두 숫자를 입력 받음
    printf("첫 번째 숫자를 입력하세요: ");
    scanf("%lf", &num1);
    printf("두 번째 숫자를 입력하세요: ");
    scanf("%lf", &num2);

    // 연산 수행
    sum = num1 + num2;
    diff = num1 - num2;
    prod = num1 * num2;
    quot = (num2 != 0) ? num1 / num2 : 0;

    // 결과 출력
    printf("합: %lf\n", sum);
    printf("차: %lf\n", diff);
    printf("곱: %lf\n", prod);
    if(num2 != 0)
        printf("나누기: %lf\n", quot);
    else
        printf("0으로 나눌 수 없습니다.\n");

    return  0;
}

