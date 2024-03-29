#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

typedef duration<double> DURATION;

const int bits_to_shift = 16;
int length = 1 << bits_to_shift;
int iterations = 4;

extern "C" void MEMCPY(u_int8_t *, u_int8_t *, int);

void HandleOptions(int argc, char ** argv) {
	int c;
	while ((c = getopt(argc, argv, "i:l:")) != -1) {
		switch (c) {
			case 'l':
				length = atoi(optarg);
				break;

			case 'i':
				iterations = atoi(optarg);
				break;

			default:
				cerr << "Usage:\n";
				cerr << "-i N	Sets number of iterations to N - default: " << length << endl;
				cerr << "-l N	Sets number of bytes to copy to N - default: " << iterations << endl;
				exit(1);
		}
	}
	cout << "Bytes to copy: " << length << endl;
	cout << "Iterations:    " << iterations << endl;
}

void Free(u_char * s, u_char * d) {
	if (s)
		free(s);
	if (d)
		free(d);
}

void InitializeSource(u_char * s, int length) {
	// No need to optimize this function as doing so would
	// give hints to the solution of the project.
	for (int i = 0; i < length; i++) {
		s[i] = rand() & 0xFF;
	}
}

bool Compare(u_char * d, u_char * s, int length) {
	// Same here. No need to optimize.
	bool retval = true;
	for (int i = 0; i < length; i++) {
		if (d[i] != s[i]) {
			retval = false;
			break;
		}
	}
	return retval;
}

int main(int argc, char **argv) {
	HandleOptions(argc, argv);
	u_int8_t * src = (u_char *) aligned_alloc(16, length);
	u_int8_t * dst = (u_char *) aligned_alloc(16, length);
	InitializeSource(src, length);
	high_resolution_clock::time_point start_time, end_time;

	start_time = high_resolution_clock::now();
	for (int i = 0; i < iterations; i++) {
		MEMCPY(dst, src, length);
	}
	end_time = high_resolution_clock::now();
	DURATION elapsed_time = duration_cast<DURATION>(end_time - start_time);
	cout << "Average time:  " << elapsed_time.count() / double(iterations) << endl;
	cout << "Correct copy:  " << boolalpha << Compare(dst, src, length) << endl;
	Free(src, dst);
	return 0;
}