CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp request.cpp requestqueue.cpp webserver.cpp loadbalancer.cpp logmanager.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = load_balancer

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
