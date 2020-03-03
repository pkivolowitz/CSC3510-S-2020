
extern "C" void Foo(char * s);

int main(int argc, char * argv[]) {
	while (*argv != nullptr) {
		Foo(*(argv++));
	}
	return 0;
}
