all: kmeans

kmeans:
	g++ -O2 -Wall --std=c++11 src/kmeans.cpp -o kmeans
