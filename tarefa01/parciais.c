#include <stdio.h>

void soma (int quantidade, int lista[]) {  //faz a soma dos elementos da lista
    for (int i=1; i<quantidade; i++) { 
        lista[i] = lista[i] + lista [i-1];
    }
}

void inverte (int quantidade, int lista[], int listainvertida[]) { //inverte os elementos da lista
    for (int i=0; i<quantidade; i++) {
        listainvertida[(quantidade-1)- i] = lista[i];
    }
}

void imprime (int quantidade, int lista[]) {
    for (int i=0; i<quantidade; i++){ //imprime a lista
        printf("%d ", lista[i]);
    }

}

int main () {
    int quantidade;
    scanf("%d", &quantidade);
    int lista[1000]; //cria uma lista com o tamanho limite

 //armazena os scanfs na lista de tamanho quantidade
    for (int i=0; i<quantidade; i++) {
        scanf("%d", &lista[i]);
    }
    soma(quantidade,lista);

    int listainvertida[1000];
    inverte(quantidade, lista, listainvertida);

    imprime(quantidade, listainvertida);

    return 0;
}