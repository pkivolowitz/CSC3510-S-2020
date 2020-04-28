/*	Perry Kivolowitz @ Carthage College
	Use / Copy / Modify freely.
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <chrono>
#include <vector>
#include <iomanip>
#include <getopt.h>

/*	Demonstration of Lock Guard versus straight Mutex

	Use of lock_guard wraps use of a mutex in a c++ object that locks a mutex during construction
	and unlocks the mutex when  the  lock_guard's destructor is called. In this way, a programmer
	cannot forget to unlock the mutex.

	A command line option of -m or -l must be specified.  These are  mutally exclusive.  If -m is
	specified, the straight mutex is used. If -l, a lock_guard / mutex is used.
*/

using namespace std;

mutex m;

/*	Notice a code block must be specified  for the lock_guard to out of scope of.  Try commenting
	the code block out and see what happens.  Second, explain what you see if you remove the call
	to yield().
*/

void LockGuardWorker(uint32_t tid) {
	while (true) {
		// Learning opportunity - try commenting these braces out.
		{
			lock_guard<mutex> l(m);
			cout << "Thread: " << setw(2) << tid << endl;
			this_thread::sleep_for(chrono::milliseconds(5));
		}
		// Learning opportunity - try commenting out this yield().
		this_thread::yield();
	}
}

void MutexWorker(uint32_t tid) {
	while (true) {
		m.lock();
		cout << "Thread: " << setw(2) << tid << endl;
		if (rand() % 30000) {
			m.unlock();
		}
		this_thread::sleep_for(chrono::milliseconds(5));
	}
}

void CheckExclusive(int mode) {
	if (mode >= 0) {
		cerr << "-m and -l are mutually exclusive\n";
		exit(1);
	}
}


int main(int argc, char ** argv) {
	vector<thread *> workers;
	const int MAX_THREADS = 64;
	int c;
	int mode = -1;

	while ((c = getopt(argc, argv, "ml")) != -1) {
		switch (c) {
			case 'm':
				CheckExclusive(mode);
				mode = 0;
				break;
			
			case 'l':
				CheckExclusive(mode);
				mode = 1;
		}
	}

	if (mode < 0) {
		cerr << "One of -m and -l must be given\n";
		exit(1);
	}

	if (mode == 0)
		cout << "Mutex will be used - will deadlock - use ^C to terminate\n";
	else
		cout << "Lock Guard / Mutex will be used - will NOT deadlock - use ^C to terminate\n";


	cout << "Hit enter / return to begin: ";
	cin.get();

	srand(uint32_t(time(nullptr)));
	for (int i = 0; i < MAX_THREADS; i++) {
			workers.push_back(new thread(((mode == 0) ? MutexWorker : LockGuardWorker), i));
	}
	for (auto & t : workers) {
		t->join();
	}
	return 0;
}