#
#
#

CC = g++
CFLAGS  = -g -Wall -std=c++0x

imgsrv: server.o main.o udpclientserver.o
	$(CC) $(CFLAGS) main.o server.o udpclientserver.o -o imgsrv

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

udpclientserver.o : udpclientserver.cpp
	$(CC) $(CFLAGS) -c udpclientserver.cpp -o udpclientserver.o

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp -o server.o


