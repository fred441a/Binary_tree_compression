fred_pile: main.o
	g++ main.o -o fred_pile

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm main.o
