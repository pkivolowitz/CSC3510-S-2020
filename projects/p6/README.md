# Free for all (Build your own semaphore)

Imagine there are only four trays available in the cafeteria and an infinite number of people lined up to eat. This project models the availability of a finite number of resources being doled out to a larger number of clients.

A synchronization primitive tailor made for this kind of problem is
the `semaphore`.

Conceived by [Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra), the semaphore is a combination of a `mutex` and a `condition variable`. We have studied both.

## Semaphores

The idea behind semaphores is that there is some kind of protected counter. Three operations are provided by the semaphore. These are:

### Initialization

The counter must be initialized to something when the semaphore is created.

### Wait

If decrementing the counter would result in a value of less than zero, the thread becomes blocked until such a time where the decremement can take place. Think of this as consuming a resource.

### Post

When a resource is no longer needed, a post operation increases the counter and notifies one or more blocked parties to wake up and try for the resource again. The choice of waking up one or many waiting threads is implementation dependent.

## Why do we need to build our own semaphore?

In an ideal world, the only reason to build our own is to learn how they are built. In the real world, there's Apple. Apple took the perfectly find POSIX implementation from pthread and deprecated it. Why? Apple.

C++ provides a platform agnostic semaphore implementation but only in C++ version 20. We teach C++ version 11.

## Your implementation of a semaphore

You are to implement this class:

```c++
class Semaphore {
	private:
		// Your innards go here.

	public:
		Semaphore(int32_t initial_value) {
			// Your code goes here.
		}

		void Post() {
			// Your code goes here.
		}

		int32_t Wait() {
			// Your code goes here.
		}
};
```

You must use a mutex, a condition variable and a counter.

## Broken worker

You are given this broken worker:

```c++
void VeryBrokenWorker(int32_t tid) {
	while (keep_going) {
		if (currently_allocated_resources < maximum_number_of_resources) {
			int32_t my_resource = ++currently_allocated_resources;
			cout << "Thread: " << setw(3) << tid << " got resource ";
			if (my_resource < 1)
				cout << " TOO SMALL\n";
			else if (my_resource > maximum_number_of_resources)
				cout << " TOO LARGE\n";
			else
				cout << endl;
			this_thread::sleep_for(chrono::milliseconds(rand() % 100 + 10));
			currently_allocated_resources--;
			cout << "Thread: " << setw(3) << tid << " releasing resource\n";
			this_thread::sleep_for(chrono::milliseconds(rand() % 100 + 10));
		}
	}
}
```

The loop terminates after a few seconds when the main thread sets `keep_going` to false.

This worker is very broken. Not only does it allow more than `maximum_number_of_resources` to be consumed at any given time, the print out it produces gets all jumbled.

The workers (all of them) will try to get a resource. After getting one:

* they will sleep a random amount of time simulating them doing useful work
* they release the resource
* they sleep a random amount of time simulating doing other things

```text
Thread: Thread:   4 got resource 
  7 releasing resource
Thread:   1 releasing resource
Thread:   6 got resource  TOO SMALL
Thread:   5 got resource 
Thread: Thread:   3 got resource 2 got resource 
```

## Reducing the VeryBrokenWorker to BrokenWorker

Your first job is to ensure that the output of the broken worker is not jumbled up. Modify `VeryBrokenWorker()` to merely `BrokenWorker()`.

## Fixing the BrokenWorker to produce FixedWorker

You final job is to modify BrokenWorker to use your newly built semaphore to make FixedWorker.

Here is an example of the BrokenWorker. Tip offs that it is broken include:

* `TOO SMALL` was printed. Too many resources were dispensed
* 6 releases in a row were performed - on only 4 resources?

```text
Thread:   1 got resource TOO SMALL
Thread:   0 got resource TOO SMALL
Thread:   2 got resource 
Thread:   5 releasing resource
Thread:   3 got resource 
Thread:   5 got resource 
Thread:   7 got resource 
Thread:   0 releasing resource
Thread:   4 got resource 
Thread:   3 releasing resource
Thread:   1 releasing resource
Thread:   5 releasing resource
Thread:   4 releasing resource
Thread:   2 releasing resource
Thread:   7 releasing resource
```

## Command line arguments

The provided framework allows for three command line options.

| option | meaning |
| ------ | ------- |
| w | use your fixed worker |
| b | use your broken worker |
| v | use my very broken worker |

Notice you have 3 choices of function to call. These all will have the same function signature. It would be silly to have an if statement launching one of the three functions in the creation of your threads.

Instead use a function pointer. You need practice with these.

## Work rules

All work is solo.

## Due date

This project is assigned on a Thursday. It will be due the Tuesday after next (12 days).
