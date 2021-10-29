#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cstdint>
#include <getopt.h>
#include <iomanip>
#include <chrono>

using namespace std;

atomic<uint64_t> counter{0};

void Worker(uint64_t c) {
	for (uint64_t i = 0; i < c; i++)
		counter++;
}

int main(int argc, char * argv[]) {
	uint64_t max = 1 << 10;
	int c;

	while ((c = getopt(argc, argv, "m:l")) != -1) {
		switch (c) {
			case 'm':
				max = atoi(optarg);
				break;

			case 'l':
				cout << left << setw(16) << "is_lock_free: " << boolalpha << counter.is_lock_free() << endl;
		}
	}

	cout << "ATOMIC:\n";
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

	cout << "Elapsed time in milliseconds: "
		 << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()
		 << " µs" << endl;

	return 0;
}
