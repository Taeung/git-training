package sort;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class problem{
/*개인적인 생각
문제에서는 1천으로 제한을 둬서 list을 굳이 만들필요는 없엇지만 시간은 충분하니 그냥 씀.
path를 더 보기 좋게 static으로 놓는게 좋아보긴하나, 지역변수로 사라져도 되는것이라고 생각함.  사용자에따라 고르면 될것같다.
*/
	public static int num;// 횟수
	public static ArrayList<Integer> list;
	public static int[] sol = new int[3];
	public static int val;
	 
	static Scanner sc;

	public static void main(String[] args) {
		double start = System.currentTimeMillis();
		double end;
		intro();
		for (int i = 0; i < num; i++) {
			isPrime();
			System.out.println();
			problem();
			for (int x : sol)
				System.out.print(x + " ");
			
		}
		sc.close();//(수정)scanner 끄기 추가
		
		System.out.println();
		end = System.currentTimeMillis();
		System.out.println((end - start) / 10000 + "초");
		
	}

	// 뒤에서부터 해결
	// 주어진 수의 2배이하를 부터 주변검색
	//
	public static void intro() {
		//패치로 input을 받게 수정함.
		String path = "C:\\Users\\USER\\Documents\\숙제\\3-1\\문해프\\1차과제\\prime_input.txt";
		try {
			sc = new Scanner(new File(path));
		}catch(FileNotFoundException e) {}
		num = sc.nextInt();
		
	}

	public static void problem() {
		boolean Nzero = true;
		int count = 1;
		int add_sum = 0;
		while (Nzero) {
			add_sum = val - list.get(list.size() - count);

			slow_move: for (int i = 0; i < list.size(); i++) {
				if (list.get(i) + list.get(i) > add_sum)
					break;
				for (int k = 0; k < list.size(); k++) {
					if (list.get(i) + list.get(k) > add_sum)
						break;
					if (list.get(i) + list.get(k) == add_sum) {
						sol[0] = list.get(list.size() - count);
						sol[1] = list.get(i);
						sol[2] = list.get(k);
						Nzero = false;
						break slow_move;
					}

				}
			}
			count += 1;
		}

	}

	public static void isPrime() {
		val = sc.nextInt();
		list = new ArrayList();
		if (val == 1)
			;
		for (int i = 2; i <= val; i++) {
			boolean isP = true;
			for (int k = 2; k < i; k++) {
				if (i % k == 0) {
					isP = false;
					break;
				}
			}
			if (isP)
				list.add(i);
		}

	}

}
 