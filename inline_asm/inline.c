#include <stdio.h>
#include <assert.h>

/*	This is an example of the "new" GNU portable assembly language.
	It is a nice example of wonks gone wild. This really isn't very
	useful any more. Don't be a wonk.
*/
int ADD(int i, int j)
{
  int res = 0;
  __asm (
	"ADD %[result], %[input_i], %[input_j]"
    : [result] "=r" (res)
    :	[input_i] "r" (i), 
		[input_j] "r" (j)
  );
  return res;
}

/*	This is an example of non-portable inline assembly language.
	Nothing could be simpler!
*/
int UDIV(int i, int j)
{
	asm (
		"udiv	w0, w0, w1\n"
	);
}

/*	This is an example of non-portable inline assembly language.
	Nothing could be simpler!
*/
int MOD(int i, int j)
{
	asm (
		"udiv	w2, w0, w1\n"
		"mul	w2, w2, w1\n"
		"sub	w0, w0, w2\n"
	);
}
int main(void)
{
  int a = 1;
  int b = 2;
  int c = 0;

  c = ADD(a,b);
  printf("Result of %d + %d = %d\n", a, b, c);
  c = UDIV(9,8);
  printf("Result of %d / %d = %d\n", 9, 8, c);
  assert(c == (9 / 8));
  c = MOD(9,8);
  printf("Result of %d MOD %d = %d\n", 9, 8, c);
  assert(c == (9 % 8));
}
