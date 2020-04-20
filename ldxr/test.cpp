#include <thread>
#include <mutex>

using namespace std;

mutex lll;
volatile int x = 0;
void Foo() {
	lll.lock();
	x++;
	x++;
	x++;
	x++;
	x++;
	lll.unlock();
}
