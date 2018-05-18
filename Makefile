all: kmeans

tmp/kmeans.o: src/kmeans.cpp src/functions.h src/globals.h
	g++ -O2 -g -c --std=c++11 src/kmeans.cpp -o tmp/kmeans.o

kmeans: tmp/kmeans.o
	g++ -O2 -g --std=c++11 tmp/kmeans.o -o kmeans

clean:
	rm kmeans
	rm tmp/*
	touch tmp/placeholder.tmp
