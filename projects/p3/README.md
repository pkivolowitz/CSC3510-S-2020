# Floating Point Programming

I have assigned this program often in CS 1 and even CS 0. 

The idea is to choose two random numbers from zero to one, inclusive. Treat these as an x and y coordinate. Calculate the distance to the origin. If the distance puts the point inside the unit circle, record the trial as a hit. 

Finally, divide the number of hits by the number of trials and multiply by four. The result will be an approximation of PI using stochastic methods.

## Number of trials to run

This will come from the command line as in:

```text
user@comporg:~/pi$ ./a.out 100000
Executing: 100000 iterations.
Hits: 78443
Approximation: 3.137720
user@comporg:~/pi$
```

If the command line argument is *not* given, use a default of 100000.

Remember that all AARCH64 instructions are 32 bits long. An implication of this is you can't simply do:

```text
	mov			x0, 1000000
```

## Vetting the command line argument

You are not responsible for doing this.

## Converting command line argument to integer

`atoi`

## Seeding the random number generator

In your previous C++ programs, you will have done (code snippets follow):

```c++
#include <ctime>

	srand((unsigned int) time(nullptr));
```

You must seed the RNG in this way. But in assembly language.

## Getting a random number in the right range

`rand()` return an integer between 0 and `RAND_MAX`. In C++ you would do:

```c++
	float v = float(rand()) / float(RAND_MAX);
```

You must do this in your program. What value is RAND_MAX? Write a tiny C++ program on the ARM and print out the value.

You must write a subroutine (function) which returns a random number in the right range. Call it `randf` so I can find it easily.

## Converting integers to doubles

In the above, you converted integers to floats with a cast. In assembly language you must code the instructions which perform the cast yourself. Look up `scvtf`.

## FP registers

Just like `x0` through `x30`, there exists `d0` through `d30`. In the float registers, `d29` and `d30` are not special. However, non-scratch float registers must still be saved and restored in functions.

## FP ops

You'll use instructions like `fmul`, `fdiv`, `fsqrt`, `fmov` and `fcmp`.

## Printing FP

`printf` will be your friend. Like always, the format string address goes in `x0`. A `%f` found in the format string tells `printf` to look in the FP registers starting with `d0` as the first value.

## Partner rules

No partners

## Due date

This program is assign on March 3. It will be due on March 17, an ungodly long time for this assignment.

