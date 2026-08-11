#include <stdio.h>
#include <stdbool.h>

int main() {
  printf("Quantas vértices?");
  int n;
  scanf("%d", &n);

  int matriz[n][n];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){
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
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++){
      printf("%d\t", matriz[i][j]);
    }
    printf("\n");
  }

  int visitados[n];
  for (int i = 0; i < n; i++){
    visitados[i] = 0;
  }

  printf("Escolha um nó inicial: ");
  int inicio;
  scanf("%d", &inicio);
  int atual = inicio;
  visitados[inicio - 1] = 1;
  printf("\nVisitamos: %d\n", inicio);

  int topo = 0;
  int pilha[n + 1];
  pilha[topo++] = atual;

  bool parar = false;
  while (!parar) {
    //se a pilha estiver vazia procurar um novo nó não visitado
    if (topo == 0) {
      int novo = -1;
      for (int i = 0; i < n; i++) {
        if (!visitados[i]) { //tem que verificar se foi visitado um por um
          novo = i + 1;
          break;
        }
      }

      if (novo == -1) {
        parar = true;  //todos visitados
      }else {
        atual = novo;
        visitados[atual - 1] = 1;
        pilha[topo++] = atual;
        printf("Visitamos: %d\n", atual);
      }
    }

    //Percorre a linha no atual
    for (int j = 0; j < n; j++) {
      if (matriz[atual - 1][j] == 1) {
        if (!visitados[j]) {
          atual = j + 1;
          visitados[atual - 1] = 1;
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
      if (visitados[i]) {
        cont++;
      }
      if (cont == n) {
        printf("Já visitamos tudo.\n");
        parar = true;
      }
    }
  }

  return 0;
}