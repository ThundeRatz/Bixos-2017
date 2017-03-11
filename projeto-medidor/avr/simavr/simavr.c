/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 ThundeRatz
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sim_avr.h>
#include <sim_elf.h>
#include <sim_gdb.h>

#include "uart_pty.h"

avr_t *avr = NULL;

void usage(const char *program_name) {
	fprintf(stderr, "Uso: %s [flags] firmaware_alvo\n"
			"\tFlags: -g - Esperar GDB na porta 1234\n", program_name);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		usage(argv[0]);
		return -1;
	}

	elf_firmware_t firmware;
	char *filename;
	int debug = 0;

	int option;
	for (option = getopt(argc, argv, "g"); option != -1; option = getopt(argc, argv, "g")) {
		switch (option) {
		case '?':
			return -1;

		case 'g':
			debug = 1;
			break;
		}
	}

	if (optind != argc - 1) {
		usage(argv[0]);
		return -1;
	}

	filename = argv[optind];

	if (elf_read_firmware(filename, &firmware)) {
		fprintf(stderr, "elf_read_firmware falhou\n");
		return -1;
	}

	printf("Firmware %s freq = %" PRIu32 " mmcu = %s\n", argv[1], firmware.frequency, firmware.mmcu);

	avr = avr_make_mcu_by_name(firmware.mmcu);
	if (!avr) {
		fprintf(stderr, "MCU '%s' desconhecido\n", firmware.mmcu);
		exit(1);
	}
	avr_init(avr);
	avr_load_firmware(avr, &firmware);

	if (debug) {
		avr->gdb_port = 1234;
		avr->state = cpu_Stopped;
		avr_gdb_init(avr);
	}

	uart_pty_t uart_pty;
	uart_pty_init(avr, &uart_pty);
	uart_pty_connect(&uart_pty, '0');

	int state;
	for (state = cpu_Running; (state != cpu_Done) && (state != cpu_Crashed); state = avr_run(avr)) ;

	uart_pty_stop(&uart_pty);

	if (state == cpu_Done) {
		printf("Emulação terminada\n");
		return 0;
	}

	printf("Erro na execução\n");
	return -1;
}
