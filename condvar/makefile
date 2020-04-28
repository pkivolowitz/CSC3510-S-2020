CPPFLAGS	= -Wall -std=c++11 -g
CFLAGS 		= -Wall -g
CXX			= g++
CC			= gcc

pthread		: 	pthread_version.c
			$(CC) $(CFLAGS) -o $@ $< -lpthread

clean		:
			rm -f *.o demo
