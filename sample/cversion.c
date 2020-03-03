
extern void Foo(char * s);

#define	NULL	(0)

int main(int argc, char * argv[]) {
	while (*argv != NULL) {
		Foo(*(argv++));
	}
	return 0;
}
