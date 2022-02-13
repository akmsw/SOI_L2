# author: Bonino, Francisco Ignacio.
# version: 1.1
# since: 2021-08-18

CC = gcc
CFLAGS = -Wall -Werror -pedantic
SLIBFLAGS = ar rs

all: build_folders file_utilities.o libfile_utilities.a lab2_utilities.o liblab2_utilities.a mainL2.o mainL2

build_folders:
	mkdir -p ./obj ./bin ./lib

# Librería estática propia: file_utilities.
file_utilities.o:
	$(CC) $(CFLAGS) -c src/include/file_utilities.c -o obj/file_utilities.o

libfile_utilities.a:
	$(SLIBFLAGS) lib/libfile_utilities.a obj/file_utilities.o -o lib/libfile_utilities.a

# Librería estática propia: lab2_utilities.
lab2_utilities.o:
	$(CC) $(CFLAGS) -c src/include/lab2_utilities.c -o obj/lab2_utilities.o

liblab2_utilities.a:
	$(SLIBFLAGS) lib/liblab2_utilities.a obj/lab2_utilities.o -o lib/liblab2_utilities.a

# Ejecutable mainL2.
mainL2.o:
	$(CC) $(CFLAGS) -c src/mainL2.c -o obj/mainL2.o

mainL2: obj/mainL2.o lib/libfile_utilities.a lib/liblab2_utilities.a
	$(CC) -o bin/mainL2 obj/mainL2.o lib/libfile_utilities.a lib/liblab2_utilities.a

clean:
	rm -r ./bin
	rm -r ./obj
	rm -r ./lib