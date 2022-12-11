# filter_kruskal_algorithm

Para rodar o algoritmo desejado basta rodar o programa da seguinte forma:

- `make <algoritmo_desejado>`

Dessa forma, o algoritmo irá começar a rodar e esperará o input do usuário. 

Para o algoritmo básico de Kruskal é esperado a seguinte estrutura de informações:

- `<número de vértices>`
- `<número de arestas>`
- `<vértice u> <vértice v> <peso da aresta entre u-v>`

Para o algoritmo básico de Prim é esperado a seguinte estrutura de informações:

- `<número de vértices>`
- `matriz de adjacência de um grafo com pesos`

Agora, caso você deseje rodar o programa com algum dos cases de exemplos presente nesse repositório basta realizar o seguinte comando:

- `make <algoritmo_desejado> < ./cases/<algoritmo_desejado>/<nome_input>.txt`