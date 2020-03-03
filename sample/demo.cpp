#include <iostream>

using namespace std;

struct Something {
	int a;
	char b[4];
	short c;
};

extern "C" void InitializeSomething(Something * s);

int main() {
	Something s;
	InitializeSomething(&s);
	cout << "a	" << s.a << endl;
	cout << "b[0]	" << s.b[0] << endl;
	cout << "b[1]	" << s.b[1] << endl;
	cout << "b[2]	" << s.b[2] << endl;
	cout << "b[3]	" << s.b[3] << endl;
	cout << "c 	" << s.c << endl;
	return 0;
}
