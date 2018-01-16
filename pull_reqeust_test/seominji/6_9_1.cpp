#include <iostream>
using namespace std;
class Fan () {
	int speed;
	bool on;
	double radius;
	
	Fan () {
		speed = 1;
		on = 1;
		radius = 5;
	}
	
	~Fan () {
	}
	
	void get () {
		cout<<"speed = "<<speed<<endl;
		if (on==1) cout <<"on"<<endl;
		else cout <<"off"<<endl;
		cout<<"radius = "<<radius<<endl;
	}
	
	void set (int a; bool b; double c;) {
		speed = a;
		on = b;
		c = 
	}
}

int main () {
	Fan a, b;
	a.set (3, 1, 10.0);
	b.set (2, 0, 5.0);
	a.get;
	b.get;
	system("pause");
	return 0;
	
}
