#include <stdio.h>
#include <stdbool.h>

int main() {
  printf("Quantas vértices?");
  int n;
  scanf("%d", &n);

  int matriz[n][n];
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      matriz[i][j] = 0;
    }
  }
  printf("Quantas conexões?");
  int con;
  scanf("%d", &con);

  int escolha_tipo;
  do{
    printf("Qual o tipo de ligação? \n1-arco\n2-aresta\n");
    scanf("%d", &escolha_tipo);
      if(escolha_tipo!=1&& escolha_tipo!=2){
        printf("Escolha errada, tente novamente\n");
      }
  }while(escolha_tipo!=1 && escolha_tipo!=2);

  if(escolha_tipo==1){
    for (int i = 0; i < con; i++) {
      printf("Conexao: origem-destino: ");
      int origem = 0, destino = 0;
      scanf("%d %d", &origem, &destino);
      if(origem > n || origem < 1 || destino > n|| destino < 1){
        printf("Escolha fora dos limites, tente novamente\n");
        i--;
      }else{
        matriz[origem - 1][destino - 1] = 1;
      }
    }
  }else{
    for (int i = 0; i < con; i++) {
      printf("Conexao: origem-destino: ");
      int origem = 0, destino = 0;
      scanf("%d %d", &origem, &destino);
      if(origem > n || origem < 1 || destino > n|| destino < 1){
        printf("Escolha fora dos limites, tente novamente\n");
        i--;
      }else{
        matriz[origem - 1][destino - 1] = 1;
        matriz[destino - 1][origem - 1] = 1;
      }
    }
  }
  printf("\nSua matriz:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++){
      printf("%d\t", matriz[i][j]);
    }
    printf("\n");
  }

  int visitados_DFS[n];
  for (int i = 0; i < n; i++){
    visitados_DFS[i] = 0;
  }
  int visitados_BFS[n];
  for (int i = 0; i < n; i++){
    visitados_BFS[i] = 0;
  }

  printf("Escolha um nó inicial: ");
  int inicio;
  scanf("%d", &inicio);
  int atual = inicio;
  visitados_DFS[inicio - 1] = 1;
  visitados_BFS[inicio - 1] = 1;
  printf("\nVisitamos: %d\n", inicio);

  int topo = 0;
  int pilha[n + 1];
  pilha[topo++] = atual;

  bool parar_DFS = false;
  bool parar_BFS = false;


  // PESQUISA DFS
  while (!parar_DFS) {
    //se a pilha estiver vazia procurar um novo nó não visitado
    if (topo == 0) {
      int novo = -1;
      for (int i = 0; i < n; i++) {
        if (!visitados_DFS[i]) { //tem que verificar se foi visitado um por um
          novo = i + 1;
          break;
        }
      }

      if (novo == -1) {
        parar_DFS = true;  //todos visitados
      }else {
        atual = novo;
        visitados_DFS[atual - 1] = 1;
        pilha[topo++] = atual;
        printf("Visitamos: %d\n", atual);
      }
    }

    //Percorre a linha no atual
    for (int j = 0; j < n; j++) {
      if (matriz[atual - 1][j] == 1) {
        if (!visitados_DFS[j]) {
          atual = j + 1;
          visitados_DFS[atual - 1] = 1;
          pilha[topo++] = atual;
          printf("Visitamos: %d\n", atual);
          j = 0; //recomeça pela linha do novo atual
        }
        //ignora se o j+1 ja foi visitado
      }
    }

    //quando percorre a linha e nao encontra nada, desempilha
    if (topo > 0) {
      //se eu coloco aqui topo = topo-- da falha seila pq
      atual = pilha[--topo];
    } else {
      //se a pilha zerou, o loop vai tentar encontrar um novo nó no início do while
    }

    //verifica se todos foram visitados
    int cont = 0;
    for (int i = 0; i < n; i++){
      if (visitados_DFS[i]) {
        cont++;
      }
      if (cont == n) {
        printf("Já visitamos tudo.\n");
        parar_DFS = true;
      }
    }
  }

  // PESQUISA BFS

  int inicio_fila = 0;
  int fim_fila = 0;
  int fila[n + 1];
  fila[fim_fila++] = atual;
  printf("\nVisitamos: %d\n", inicio);

  while (!parar_BFS) {
  // se a fila estiver vazia procurar um novo nó não visitado
    if (inicio_fila == fim_fila) {
      int novo = -1;

      for (int i = 0; i < n; i++) {
        if (!visitados_BFS[i]) {
          novo = i + 1;
          break;
        }
      }

      if (novo == -1) {
        parar_BFS = true;  // todos visitados
      } else {
        atual = novo;
        visitados_BFS[atual - 1] = 1;
        fila[fim_fila++] = atual;
        printf("Visitamos: %d\n", atual);
      }
    }

    // pega o primeiro elemento da fila
    if (inicio_fila < fim_fila) {
        atual = fila[inicio_fila++];

      // Percorre a linha no atual
      for (int j = 0; j < n; j++) {
        if (matriz[atual - 1][j] == 1) {
          if (!visitados_BFS[j]) {
            visitados_BFS[j] = 1;
            fila[fim_fila++] = j + 1;
            printf("Visitamos: %d\n", j + 1);
          }
          // ignora se o j+1 ja foi visitado
        }
      }
    }

      // verifica se todos foram visitados
    int cont = 0;

    for (int i = 0; i < n; i++) {
      if (visitados_BFS[i]) {
        cont++;
      }

      if (cont == n) {
        printf("Já visitamos tudo.\n");
        parar_BFS = true;
      }
    }
  }

  return 0;
}