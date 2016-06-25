#
#
#

CC = g++
CFLAGS  = -g -Wall -std=c++0x

imgsrv: server.o main.o 
	$(CC) $(CFLAGS) main.o server.o -o imgsrv

main.o: main.C
	$(CC) $(CFLAGS) -c main.C -o main.o

server.o: server.C
	$(CC) $(CFLAGS) -c server.C -o server.o


