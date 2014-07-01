All: Date.o Meeting.o User.o Storage.o
	
Date.o: Date.h Date.cpp
	g++ -std=c++11 -c -g Date.cpp 
Meeting.o: Meeting.h Meeting.cpp
	g++ -std=c++11 -c -g Meeting.cpp
User.o: User.cpp User.h
	g++ -std=c++11 -c -g User.cpp
Storage.o: Storage.h Storage.cpp
	g++ -std=c++11 -c -g Storage.cpp
clean:
	rm *.o

