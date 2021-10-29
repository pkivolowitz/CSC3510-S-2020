#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdint>
#include <getopt.h>
#include <chrono>

using namespace std;

volatile uint64_t counter = 0;

mutex bfl;

void Worker(uint64_t c) {
	for (uint64_t i = 0; i < c; i++) {
		bfl.lock();
		counter++;
		bfl.unlock();
	}
}

int main(int argc, char * argv[]) {
	uint64_t max = 1 << 10;
	int c;

	while ((c = getopt(argc, argv, "m:")) != -1) {
		switch (c) {
			case 'm':
				max = atoi(optarg);
				break;
		}
	}

	cout << "FINE GRAINED LOCK:\n";
	cout << "Thread count:   " << thread::hardware_concurrency() << endl;
	cout << "Max:            " << max << endl;
	cout << "Expected value: " << max * thread::hardware_concurrency() << endl;

	vector<thread> t(thread::hardware_concurrency());

	auto start_time = chrono::steady_clock::now();

	for (size_t i = 0; i < t.size(); i++)
		t.at(i) = thread(Worker, max);
	
	for (auto & it : t)
		it.join();
	
	cout << "Actual value:   " << counter << endl;

	auto end_time = chrono::steady_clock::now();

	cout << "Actual value:   " << counter << endl;
	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()
		 << " µs" << endl;

	return 0;
}
