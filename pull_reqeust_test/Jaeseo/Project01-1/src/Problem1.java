import java.util.Scanner;

/*
 문제1
 사용자로부터 초를 입력받아 아래와 같이 시, 분, 초로 계산하여
 출력하는 프로그램을 작성하세요.
 단, 초는 정수로 입력받아 야 하고Scanner 클래스를 활용합니다. 
 */
public class Problem1 {
	public static void main(String[] args) {
		int sec; //초를 저장할 공간(정수형 변수)
		Scanner sc = new Scanner(System.in); //Scanner 클래스 소환
		
		System.out.print("초를 입력하세요.: "); //출력
		sec = sc.nextInt(); //사용자로부터 초를 입력받기
		
		System.out.print(sec+"초: "+
		sec/3600+"시간 "+
		(sec/60)%60+"분 "+
		sec%60+"초");
		// 시간 분 초 수학적 수식으로 계산하여 출력하기
	}
}
/*
<실행결과>
초를 입력하세요: 12345
12345초: 3시간25분45초
 */