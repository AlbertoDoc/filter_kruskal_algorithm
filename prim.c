#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>


void printMST(int parent[], int numberOfVertex, int graph[numberOfVertex][numberOfVertex])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < numberOfVertex; i++){
        printf("%d - %d \t%d \n", parent[i], i,graph[i][parent[i]]);
    }
}


int findMinKey(int weightKeys[], bool mstSet[], int numberOfVertex)
{
    int min = INT_MAX; 
    int min_index;
 
    for (int i = 0; i < numberOfVertex; i++){
        if (mstSet[i] == false && weightKeys[i] < min){
            min = weightKeys[i]; 
            min_index = i;
        }
    }  
 
    return min_index;
}


void prim(int numberOfVertex,int graph[numberOfVertex][numberOfVertex], int weightKeys[], bool mstSet[],int parent[]) {
    for (int i = 0; i < numberOfVertex-1; i++){
        int min_key_index = findMinKey(weightKeys,mstSet,numberOfVertex);
        mstSet[min_key_index] = true;

        for (int j = 0; j < numberOfVertex;j++){
            if (mstSet[j] == false && graph[min_key_index][j] && graph[min_key_index][j] < weightKeys[j]){
                parent[j] = min_key_index;
                weightKeys[j] = graph[min_key_index][j];
            }
        }
    }

    printMST(parent, numberOfVertex, graph);
}

int main() {
    int numberOfVertex; 

    printf("Insira a quantidade de vertices do grafo: ");
    scanf("%d", &numberOfVertex);

    int graph[numberOfVertex][numberOfVertex];

    int parent[numberOfVertex], weightKeys[numberOfVertex];
    bool mstSet[numberOfVertex];

    for (int i = 0; i < numberOfVertex; i++){
        weightKeys[i] = INT_MAX; 
        mstSet[i] = false;
    }

    // Including first vertex in MST
    weightKeys[0] = 0;
    parent[0] = -1;
       

    for (int i = 0; i < numberOfVertex; i++) {
        printf("\nInsira a linha %d do grafo:\n",i);
        for (int j = 0; j < numberOfVertex; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    clock_t start, end;
    start = clock();
    prim(numberOfVertex, graph, weightKeys, mstSet, parent);
    end = clock();
    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("Tempo de execucao do algoritmo em segundos: %f\n", duration);
}