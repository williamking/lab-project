All: test.cpp Date.o Meeting.o User.o Storage.o AgendaService.o
	g++ -std=c++11 -o All -g test.cpp Meeting.o Storage.o AgendaService.o User.o Date.o
AgendaService.o: AgendaService.h AgendaService.cpp
	g++ -std=c++11 -c -g AgendaService.cpp
Date.o: Date.h Date.cpp
	g++ -std=c++11 -c -g Date.cpp 
Meeting.o: Meeting.h Meeting.cpp
	g++ -std=c++11 -c -g Meeting.cpp
User.o: User.cpp User.h
	g++ -std=c++11 -c -g User.cpp
Storage.o: Storage.h Storage.cpp
	g++ -std=c++11 -c -g Storage.cpp
clean:
	rm *.o All

