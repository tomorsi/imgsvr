#
#
#

CC = g++
CFLAGS  = -g -Wall -std=c++0x

imgsrv: server.o main.o udpserver.o imgudpserver.o
	$(CC) $(CFLAGS) main.o server.o imgudpserver.o udpserver.o -o imgsrv

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

udpserver.o : udpserver.cpp
	$(CC) $(CFLAGS) -c udpserver.cpp -o udpserver.o

imgudpserver.o : imgudpserver.cpp
	$(CC) $(CFLAGS) -c imgudpserver.cpp -o imgudpserver.o

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp -o server.o


