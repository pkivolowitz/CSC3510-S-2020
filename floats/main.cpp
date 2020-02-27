/*	Demonstration of floating  point error as compared to 
**	epsilon for both float  and double types.  Also shown
**	(but not  demonstrated) is where  the  float / double
**	components live.
**
**	Suitable for use in a Computer Organization class.
**
**	Perry Kivolowitz
**	Carthage College Computer Science Department
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cinttypes>

using namespace std;

template<typename T1, typename T2>
void Foo(int max)
{
	for (int i = 1; i <= max; i++) {
		T1 a = T1(1) / T1(i) * i;
		if (a != T1(1)) {
			cout << dec << "[" << setw(3) << i << "] " << setw(16) << setprecision(10) << 1.0 - a << " ";
			cout << endl;
		}
	}
}

int main() {
	cout << "float epsilon = " << numeric_limits<float>::epsilon() << ":" << endl;
	Foo<float, uint32_t>(150);
	cout << "double epsilon = " << numeric_limits<double>::epsilon() << ":" << endl;
	Foo<double, uint64_t>(150);
	return 0;
}

/*

// This would have been easier if you shift first then mask but
// the way  below is  done shows  where each component actually
// lives.

#define	DSIGN		0x8000000000000000
#define DEXPONENT	0x7FF0000000000000
#define	DMANTISSA	0x000FFFFFFFFFFFFF

#define	FSIGN		0x80000000
#define FEXPONENT	0x7F800000
#define	FMANTISSA	0x003FFFFF

			union ED {
				uint64_t u;
				double f;
			} ed;
			ed.f = a;
			cout << hex << ((ed.u & DSIGN) >> 62) << " ";
			cout << ((ed.u & DEXPONENT) >> 51) << " ";
			cout << (ed.u & DMANTISSA);


			union EF {
				uint32_t u;
				float f;
			} ef;
			ef.f = a;
			cout << hex << ((ef.u & FSIGN) >> 30) << " ";
			cout << ((ef.u & FEXPONENT) >> 21) << " ";
			cout << (ef.u & FMANTISSA);
*/
