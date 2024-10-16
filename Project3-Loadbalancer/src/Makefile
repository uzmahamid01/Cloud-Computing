CC = g++
CFLAGS = -Wall -Werror -std=c++11

all: load_balancer

load_balancer: main.o request.o webserver.o loadbalancer.o requestqueue.o
	$(CC) $(CFLAGS) -o load_balancer main.o request.o webserver.o loadbalancer.o requestqueue.o

main.o: main.cpp request.h webserver.h loadbalancer.h requestqueue.h
	$(CC) $(CFLAGS) -c main.cpp

request.o: request.cpp request.h
	$(CC) $(CFLAGS) -c request.cpp

webserver.o: webserver.cpp webserver.h request.h
	$(CC) $(CFLAGS) -c webserver.cpp

loadbalancer.o: loadbalancer.cpp loadbalancer.h request.h requestqueue.h
	$(CC) $(CFLAGS) -c loadbalancer.cpp

requestqueue.o: requestqueue.cpp requestqueue.h
	$(CC) $(CFLAGS) -c requestqueue.cpp

clean:
	rm -f load_balancer *.o
