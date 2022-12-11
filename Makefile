CC = gcc

build-kruskal:
	gcc kruskal.c -o kruskal

build-prim:
	gcc prim.c -o prim

kruskal: build-kruskal
	./kruskal

prim: build-prim
	./prim