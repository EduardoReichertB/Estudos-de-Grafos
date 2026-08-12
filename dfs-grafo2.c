
#include <stdio.h>
#include <stdbool.h>

void DFS(int vertices, int matriz[vertices][vertices], int inicio) {

    int visitados[vertices];

    // Inicializa todos os vértices como não visitados
    for (int i = 0; i < vertices; i++) {
        visitados[i] = 0;
    }

    // Pilha
    int pilha[vertices];
    int topo = 0;

    // Converte o vértice informado pelo usuário
    // para o índice da matriz
    int atual = inicio - 1;

    // Marca o vértice inicial como visitado
    visitados[atual] = 1;

    // Coloca o vértice inicial na pilha
    pilha[topo++] = atual;

    printf("\nDFS: ");

    while (topo > 0) {

        // Retira o último vértice colocado na pilha
        atual = pilha[--topo];

        printf("%d ", atual + 1);

        // Procura os vizinhos
        for (int j = 0; j < vertices; j++) {

            if (matriz[atual][j] == 1 && !visitados[j]) {

                // Marca o vértice como visitado
                visitados[j] = 1;

                // Coloca o vértice na pilha
                pilha[topo++] = j;
            }
        }
    }

    printf("\n");
}

void BFS(int vertices, int matriz[vertices][vertices], int inicio) {
    int visitados[vertices];

    // Inicializa todos como não visitados
    for (int i = 0; i < vertices; i++) {
        visitados[i] = 0;
    }

    // Fila
    int fila[vertices];
    int inicioFila = 0;
    int fimFila = 0;

    // Converte o vértice para índice da matriz
    int atual = inicio - 1;

    // Marca o inicial como visitado e coloca na fila
    visitados[atual] = 1;
    fila[fimFila++] = atual;

    printf("\nBFS: ");

    while (inicioFila < fimFila) {

        // Retira o primeiro da fila
        atual = fila[inicioFila++];

        printf("%d ", atual + 1);

        // Procura os vizinhos
        for (int j = 0; j < vertices; j++) {

            if (matriz[atual][j] == 1 && !visitados[j]) {

                // Marca como visitado
                visitados[j] = 1;

                // Coloca no final da fila
                fila[fimFila++] = j;
            }
        }
    }

    printf("\n");
}


int main() {

    printf("Quantas vértices?");
    int vertice;
    scanf("%d", &vertice);

    int matriz[vertice][vertice];

    for (int i = 0; i < vertice; i++)
        for (int j = 0; j < vertice; j++) {
            matriz[i][j] = 0;
        }

    printf("Quantas conexões?");
    int con;
    scanf("%d", &con);

    for (int i = 0; i < con; i++) {

        printf("Conexao: origem-destino: ");

        int origem = 0, destino = 0;

        scanf("%d %d", &origem, &destino);

        matriz[origem - 1][destino - 1] = 1;
        matriz[destino - 1][origem - 1] = 1;
    }

    printf("\nSua matriz:\n");

    for (int i = 0; i < vertice; i++) {

        for (int j = 0; j < vertice; j++) {
            printf("%d\t", matriz[i][j]);
        }

        printf("\n");
    }

    printf("Escolha um nó inicial: ");

    int inicio;
    scanf("%d", &inicio);

    // Chama a função DFS
    DFS(vertice, matriz, inicio);

    return 0;
}