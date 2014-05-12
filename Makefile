simulator: Event.o LinkedList.o Packets.o main.o 
	g++ -ansi -Wall -g -o simulator Event.o LinkedList.o Packets.o main.o 

Event.o: Event.cpp Event.h  
	g++ -ansi -Wall -g -c Event.cpp

LinkedList.o: LinkedList.cpp LinkedList.h  
	g++ -ansi -Wall -g -c LinkedList.cpp

Packets.o: Packets.cpp Packets.h  
	g++ -ansi -Wall -g -c Packets.cpp

main.o: main.cpp Event.h LinkedList.h Packets.h  
	g++ -ansi -Wall -g -c main.cpp

clean: 
	rm -f simulator Event.o LinkedList.o Packets.o main.o 