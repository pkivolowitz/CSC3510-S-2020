#include <iostream>
#include <thread>
#include <vector>
#include <cstdint>
#include <getopt.h>

using namespace std;

volatile uint64_t counter = 0;

vector<uint64_t> counters;

void Worker(uint64_t c, int tid) {
	volatile uint64_t counter = 0;
	for (uint64_t i = 0; i < c; i++)
		counter++;
	counters.at(tid) = counter;
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

	cout << "ROLL UP:\n";
	cout << "Thread count:   " << thread::hardware_concurrency() << endl;
	cout << "Max:            " << max << endl;
	cout << "Expected value: " << max * thread::hardware_concurrency() << endl;

	vector<thread> t(thread::hardware_concurrency());
	counters.resize(t.size());

	auto start_time = chrono::steady_clock::now();

	for (size_t i = 0; i < t.size(); i++)
		t.at(i) = thread(Worker, max, i);

	uint64_t sum = 0;

	for (size_t i = 0; i < t.size(); i++) {
		t.at(i).join();
		sum += counters.at(i);
	}

	cout << "Actual value:   " << sum << endl;

	auto end_time = chrono::steady_clock::now();

	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()
		 << " µs" << endl;

	return 0;
}
