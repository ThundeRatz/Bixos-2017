.PHONY: all clean

all: hello

clean:
	rm -f *.o hello

hello: hello.o main.o
	gcc -o $@ $^

main.o: main.c

hello.o: hello.c
