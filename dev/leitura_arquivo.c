#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Uso: %s arquivo\n", argv[0]);
		return -1;
	}

	int fd;
	// Tenta abrir em apenas leitura.
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		// Se abertura falhou, open retorna -1.
		// A função perror mostra na tela a razão da falho.
		perror("open");
		return -1;
	}

	for (;;) {
		char buffer[40];
		ssize_t count;

		// read retorna o número de bytes lidos, que é salvo na variável count.
		// Se for -1, indica que houve erro. Se for 0, indica que o arquivo acabou.
		count = read(fd, buffer, sizeof(buffer));

		switch (count) {
		case -1:
			perror("read");
			return -1;

		case 0:
			// Fim do arquivo, fecha e termina o programa.
			close(fd);
			return 0;

		default:
			{
				// Se chegou aqui, a leitura deu certo e você pode fazer alguma
				// coisa com os dados.
				int i;

				// Apenas um exemplo, mostra os dados em hexadecimal e ASCII.
				for (i = 0; i < count; i++)
					printf("%.2hhx ", buffer[i]);
				printf("\n");
				for (i = 0; i < count; i++)
					printf(" %c ", isprint(buffer[i]) ? buffer[i] : '.');
				printf("\n");
			}
		}
	}
}
