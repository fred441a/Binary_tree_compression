fred_pile: main.o
	g++ main.o -o fredPresser

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o
	rm *.out
