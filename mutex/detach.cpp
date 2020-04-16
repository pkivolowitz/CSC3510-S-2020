#include <iostream>
#include <thread>
#include <getopt.h>
#include <chrono>
#include <vector>

/*	This program demonstrates that even if a thread is detatched, it will
	terminate when the parent terminates. Note that a detached thread can
	not be joined.

	watch ps -M
*/

using namespace std;

void Worker(int tid) {
	// Thread 0 is going to "try" to live longer than the others.
	int time_to_sleep = (tid == 0) ? 10 : 3;

	std::cout << "Starting thread: " << tid << endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_to_sleep));
	std::cout << "Ending thread:   " << tid << endl;
}

int main(int argc, char * argv[]) {
	vector<thread> t(thread::hardware_concurrency());

	for (size_t i = 0; i < t.size(); i++) {
		t.at(i) = thread(Worker, i);
		if (i == 0) {
			t.at(i).detach();
		}
	}

	for (auto & it : t)
		if (&it != &(*t.begin()))
			it.join();
	
	return 0;
}
