#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <ctime>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


typedef struct EDGE
{
    int u;
    int v;
    int weight;
} Edge;

bool cmp(Edge u, Edge v) { 
    return u.weight < v.weight;
}

int compare(const void *a, const void *b) {
  
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
  
    return (edgeB->weight < edgeA->weight);
}

void printMST(vector<Edge> T) {
    int cost = 0;

    printf("\nArestas selecionadas para compor a MST:\nu  v  w\n");
    for (int i = 0; i < T.size(); i++) {
    	cout << T[i].u << " " << T[i].v << " " << T[i].weight << endl;
    	cost += T[i].weight;
    }

    printf("\nCusto = %d\n", cost);
}

void swap(Edge *x, Edge *y) {
    Edge temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int partition(vector<Edge> &edges, int begin, int end){
    int p = begin, pivot=edges[end].weight;
	
    for (int i = begin; i < end; i++) {
    	if (edges[i].weight <= pivot) {
    		swap(&edges[i], &edges[p]);
    		p++;
    	}
    }

    swap(&edges[end], &edges[p]);

    return p;
}

void quickSort(vector<Edge> &edges, int begin, int end) {
    int q;

    if (begin >= end) {
    	return;
    }

    q = partition(edges, begin, end);
	
    quickSort(edges, begin, q-1);
    quickSort(edges, q + 1, end);
}

int find(int u, int n, int parent[]) {
	int i = 0, A[n];
	
    while(u != parent[u]) {
		A[i] = u;
		u = parent[u];
		i++;
	}

	i--;
	
    while(i >= 0) {
		parent[A[i]] = u;
		i--;
	}

	return u;
}

void unionByRank(int u, int v, int n, int parent[], int rank[]) {
	int x, y;
	x = find(u, n, parent);
	y = find(v, n, parent);
	
    if (rank[x] < rank[y]) {
		parent[x] = y;        
    } else if (rank[y] < rank[x]) {
		parent[y] = x;
    } else {
		parent[x] = y;
		rank[y]++;
	}
}

void kruskal(vector<Edge> &edges, int n, int m, int parent[], int rank[], vector<Edge> &tree) {
    quickSort(edges, 0, m-1);

    int x, y;
    for (int i = 0; i < m; i++) {
        Edge edge = edges[i];

        if (tree.size() == n - 1) {
            // The tree is already with the maximum edges
            break;
        }
        
        // The find method uses the absolute root to determine whether two vertices belong to the same set.
        x = find(edge.u, n, parent);
        y = find(edge.v, n, parent);

        // We compare the two absolut root's to determine if they are in the same set
        // if x != y is true so, edge.u and edge.v is not in the same set
        if (x != y) {
            tree.push_back(edge);

            // Using unionByRank to make the union of two vertex
            unionByRank(x, y, n, parent, rank);
        }
    }
}

int kruskalThreshold(vector<Edge> &edges, int n, int m) {
    if (m == 0) return 1;

    int comparativeValue = edges[0].weight;
    for (int i = 1; i < m; i++) {
        if (edges[i].weight != comparativeValue) {
            return n * log(n) / 2;
        }
    }

    return m + 1;
}

vector<Edge> vectorRand(vector<Edge> &vet) {
    int k = vet.size();
    int x = rng() % k;

    vector<Edge> ans;
    set<int> used;

    for (int i = 0; i * i < k; i++) {
        while (used.count(x)) {
            x = rng() % k;
        }

        used.insert(x);
        ans.push_back(vet[x]);
    }

    return ans;
}

Edge pickPivot(vector<Edge> &edges) {
    vector<Edge> median = vectorRand(edges);
    sort(median.begin(), median.end(), cmp);

    return median[(median.size() - 1) / 2];
}

vector<Edge> filter(vector<Edge> &edges, int m, int n, int parent[], vector<Edge> &tree) {
    vector<Edge> filteredEdges;

    for (int i = 0; i < m; i++) {
        if (find(edges[i].u, n, parent) != find(edges[i].v, n, parent)) {
            filteredEdges.push_back(edges[i]);
        }
    }

    return filteredEdges;
}

void filterKruskal(int n, int m, vector<Edge> &edges, vector<Edge> &tree, int parent[], int rank[]) {
    if (m <= kruskalThreshold(edges, n, m)) {
        // runs kruskal algorithm for edge size below the threshold
        kruskal(edges, n, m, parent, rank, tree);
    } else {
        Edge pivot = pickPivot(edges);
        vector<Edge> lowestEdges;
        vector<Edge> biggestEdges;

        for (int i = 0; i < m; i++) {
            if (edges[i].weight <= pivot.weight) {
                lowestEdges.push_back(edges[i]);
            } else {
                biggestEdges.push_back(edges[i]);
            }

            filterKruskal(n, lowestEdges.size(), lowestEdges, tree, parent, rank);
            biggestEdges = filter(edges, m, n, parent, tree);
            filterKruskal(n, biggestEdges.size(), biggestEdges, tree, parent, rank);
        }
    }
}

int main() {
    int n, m;  // number of vertex and edges in graph
    int u, v, weight; // vertex u and v, weight of edge
    vector<Edge> edges;

    printf("Insira a quantidade de vertices do grafo: ");
    scanf("%d", &n);

    printf("Insira a quantidade de arestas do grafo: ");
    scanf("%d", &m);

    int parent[n + 1], rank[n + 1];

    int* vertex = (int*) malloc(n * sizeof(int));

    // giving for each vertex a identification
    for (int i = 1; i < n + 1; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        printf("\nInsira uma aresta na forma u, v, peso:\n");
        scanf("%d %d %d", &u, &v, &weight);

        Edge edge;

        edge.u = u;
        edge.v = v;
        edge.weight = weight;
        edges.push_back(edge);
    }

    quickSort(edges, 0, m-1);

    vector<Edge> tree;
    clock_t start, end;
    start = clock();
    filterKruskal(n, m, edges, tree, parent, rank);
    end = clock();

    printMST(tree);

    double duration = ((double)end - start)/CLOCKS_PER_SEC;

    printf("Tempo de execucao do algoritmo em segundos: %f\n", duration);
}