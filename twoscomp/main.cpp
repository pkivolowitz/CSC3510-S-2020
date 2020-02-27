/*	Demonstration of two's complement suitable for a
**	Computer Organization course.
**
**	Perry Kivolowitz
**	Carthage College Computer Science
*/

#include <iostream>
#include <cinttypes>
#include <iomanip>

using namespace std;

int main() {
	for (int16_t i = -16; i <= 16; i++) {
		if (i % 8 == 0 && i != 16) 
			cout << setfill(' ') << right << setw(4) << "i" << setw(4) << "Hex" << setw(4) << "  HI" << "   HI+1" << " " << setw(4) << "I+1" << endl;
		cout << setfill(' ') << right << dec << setw(4) << i;
		cout << " " << setfill('0') << setw(4) << hex << i;
		cout << " " << setw(4) << uint16_t(~i);
		cout << " " << setw(4) << uint16_t(~i + 1);
		cout << " " << setfill(' ') << setw(4) << dec << ~i + 1 << endl;
	}	
	return 0;
}
