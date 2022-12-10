CC = gcc

build-kruskal:
	gcc kruskal.c -o kruskal

build-prim:
	gcc prim.c -o prim

run-kruskal: build-kruskal
	./kruskal

run-prim: build-prim
	./prim