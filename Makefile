CC = gcc

build-kruskal:
	gcc kruskal.c -o kruskal

build-prim:
	gcc prim.c -o prim

build-filter-kruskal:
	g++ filter_kruskal.cpp -o filter_kruskal

kruskal: build-kruskal
	./kruskal

prim: build-prim
	./prim

filter-kruskal: build-filter-kruskal
	./filter_kruskal