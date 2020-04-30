CPPFLAGS	= -Wall -std=c++11 -g
OBJS		= main.o
CXX			= g++

demo		: 	$(OBJS)
			$(CXX) -o $@ $(OBJS) -lpthread

clean		:
			rm -f *.o demo
