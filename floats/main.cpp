/*	Demonstration of floating  point error as compared to 
**	epsilon for both float and double types. Suitable for
**	use in a Computer Organization class.
**
**	Perry Kivolowitz
**	Carthage College Computer Science Department
*/

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

template<typename T>
void Foo(int max)
{
	for (int i = 1; i <= max; i++) {
		T a = T(1) / T(i) * i;
		if (a != T(1))
			cout << "[" << setw(3) << i << "] " << setw(16) << setprecision(10) << 1.0 - a << endl;
	}
}

int main() {
	cout << "float epsilon = " << numeric_limits<float>::epsilon() << ":" << endl;
	Foo<float>(150);
	cout << "double epsilon = " << numeric_limits<double>::epsilon() << ":" << endl;
	Foo<double>(150);
	return 0;
}