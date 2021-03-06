all: kmeans

tmp/kmeans.o: src/kmeans.cpp src/functions.h src/globals.h
	g++ -O2 -g -c --std=c++11 src/kmeans.cpp -o tmp/kmeans.o

kmeans: tmp/kmeans.o
	g++ -O2 -g --std=c++11 tmp/kmeans.o -o kmeans
	rm tmp/kmeans.o

clean:
	rm kmeans
	rm tmp/*
	rm *-results.txt
	touch tmp/placeholder.tmp
