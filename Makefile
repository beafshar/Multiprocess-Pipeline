all: StoreCalculator.out assets.out province.out city.out store.out

StoreCalculator.out: main.o tools.o
	g++ main.o tools.o -o StoreCalculator.out

assets.out: assets.o  tools.o
	g++  assets.o tools.o -o assets.out

province.out: province.o tools.o
	g++ province.o tools.o -o province.out

city.out: city.o tools.o
	g++ city.o tools.o -o city.out

store.out: store.o tools.o
	g++ store.o tools.o -o store.out

main.o: main.cpp tools.h
	g++ -c main.cpp  -o main.o

assets.o: assets.cpp  tools.h
	g++ -c assets.cpp   -o assets.o

province.o: province.cpp  tools.h
	g++ -c province.cpp  -o province.o

city.o: city.cpp  tools.h
	g++ -c city.cpp   -o city.o

store.o: store.cpp tools.h
	g++ -c store.cpp  -o store.o

tools.o: tools.cpp tools.h 
	g++ -c tools.cpp -o tools.o

clean:
	rm *.o
	rm *.out
