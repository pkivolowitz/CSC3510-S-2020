CPPFLAGS	= -Wall -std=c++11 -O3
CFLAGS 		= -Wall -O3
CXX			= g++
CC			= gcc

all			: blabby1 blabby2 blabby3 counter1 counter2 counter3 counter4 counter5


blabby1		:	blabby1.cpp
			$(CXX) $(CPPFLAGS) -o $@ $<

blabby2		:	blabby2.cpp
			$(CXX) $(CPPFLAGS) -o $@ $<

blabby3		:	blabby3.cpp
			$(CXX) $(CPPFLAGS) -o $@ $<

counter1	:	counter1.cpp 
			$(CXX) $(CPPFLAGS) -o $@ $<

counter2	:	counter2.cpp 
			$(CXX) $(CPPFLAGS) -o $@ $<

counter3	:	counter3.cpp 
			$(CXX) $(CPPFLAGS) -o $@ $<

counter4	:	counter4.cpp 
			$(CXX) $(CPPFLAGS) -o $@ $<

counter5	:	counter5.cpp 
			$(CXX) $(CPPFLAGS) -o $@ $<

clean		:
			rm -f *.o blabby1 blabby2 blabby3 counter1 counter2 counter3 counter4 counter5
			rm -rf *.dSYM
