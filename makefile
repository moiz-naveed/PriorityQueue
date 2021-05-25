CC = gcc

CFLAGS = -std=c99 -pedantic -Wall -c -Iinclude

all:
	make build
	
main.o:
	$(CC) $(CFLAGS) src/main.c -o bin/main.o

testmain.o:
	$(CC) $(CFLAGS) src/testmain.c -o bin/testmain.o


linkedlistAPI.o:
	$(CC) $(CFLAGS) src/linkedlistAPI.c -o bin/linkedlistAPI.o		

client.o:
	$(CC) $(CFLAGS) src/client.c -o bin/client.o

build:  main.o linkedlistAPI.o client.o testmain.o
	$(CC) bin/main.o bin/linkedlistAPI.o bin/client.o -Iinclude -o bin/runMe
	$(CC) bin/testmain.o bin/linkedlistAPI.o bin/client.o -Iinclude -o bin/testMe   

run:
	./bin/runMe
clean:
	rm bin/*.o
	rm bin//runMe
	rm bin//testMe
