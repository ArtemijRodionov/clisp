#include <stdio.h>

void outputHelloWorld(int count) {
	int i = 0;
	while (i < count) {
		puts("Hello world");
		++i;
	}
	puts("\n");
}

int main(int argc, char** argv) {
	puts("Hello world");
	puts("\n");

	for (int i = 0; i < 5; ++i){
		puts("Hello world");
	}

	puts("\n");

	int i = 0;
	while (i < 5) {
		i ++;
		puts("Hello world");
	}

	puts("\n");

	outputHelloWorld(5);

	return 0;
}
