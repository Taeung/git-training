package sort;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class problem{
/*�������� ����
���������� 1õ���� ������ �ּ� list�� ���� �����ʿ�� �������� �ð��� ����ϴ� �׳� ��.
path�� �� ���� ���� static���� ���°� ���ƺ����ϳ�, ���������� ������� �Ǵ°��̶�� ������.  ����ڿ����� ���� �ɰͰ���.
*/
	public static int num;// Ƚ��
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
		sc.close();//(����)scanner ���� �߰�
		
		System.out.println();
		end = System.currentTimeMillis();
		System.out.println((end - start) / 10000 + "��");
		
	}

	// �ڿ������� �ذ�
	// �־��� ���� 2�����ϸ� ���� �ֺ��˻�
	//
	public static void intro() {
		//��ġ�� input�� �ް� ������.
		String path = "C:\\Users\\USER\\Documents\\����\\3-1\\������\\1������\\prime_input.txt";
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
 