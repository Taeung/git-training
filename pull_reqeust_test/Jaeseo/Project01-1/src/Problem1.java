import java.util.Scanner;

/*
 ����1
 ����ڷκ��� �ʸ� �Է¹޾� �Ʒ��� ���� ��, ��, �ʷ� ����Ͽ�
 ����ϴ� ���α׷��� �ۼ��ϼ���.
 ��, �ʴ� ������ �Է¹޾� �� �ϰ�Scanner Ŭ������ Ȱ���մϴ�. 
 */
public class Problem1 {
	public static void main(String[] args) {
		int sec; //�ʸ� ������ ����(������ ����)
		Scanner sc = new Scanner(System.in); //Scanner Ŭ���� ��ȯ
		
		System.out.print("�ʸ� �Է��ϼ���.: "); //���
		sec = sc.nextInt(); //����ڷκ��� �ʸ� �Է¹ޱ�
		
		System.out.print(sec+"��: "+
		sec/3600+"�ð� "+
		(sec/60)%60+"�� "+
		sec%60+"��");
		// �ð� �� �� ������ �������� ����Ͽ� ����ϱ�
	}
}
/*
<������>
�ʸ� �Է��ϼ���: 12345
12345��: 3�ð�25��45��
 */