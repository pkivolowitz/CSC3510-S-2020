
extern void Foo(char * s);

int main(int argc, char * argv[]) {
	while (*argv != NULL) {
		Foo(*(argv++));
	}
	return 0;
}
