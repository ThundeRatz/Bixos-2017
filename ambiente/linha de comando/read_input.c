#include <stdio.h>

int main() {
	char input[90];
	while (fgets(input, sizeof(input), stdin)) {
		printf("Meu programa recebeu %s\n", input);
	}
	return 0;
}
