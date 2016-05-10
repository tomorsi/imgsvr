#
#
#

CC = gcc
CFLAGS  = -g -Wall

imgsrv: server.o main.o select.o
	$(CC) $(CFLAGS) main.o server.o select.o -o imgsrv

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

select.o: select.c
	$(CC) $(CFLAGS) -c select.c -o select.o

