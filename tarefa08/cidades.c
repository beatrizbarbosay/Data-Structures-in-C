#include <stdio.h>
#include <stdlib.h>
typedef struct no* ponteiro; //abreviacao
struct regiao { //estrutura de cada nó
    char nome;
    ponteiro noroeste;
    ponteiro nordeste;
    ponteiro sudoeste;
    ponteiro sudeste;
};

typedef struct mapa{
    ponteiro raiz;
} mapa;

ponteiro criarno(char nome) { //funcao para adicionar novos espaços
    ponteiro novo =  malloc(sizeof(struct regiao));
    novo->valor = nome;
    novo->noroeste = NULL;
    novo->nordeste = NULL;
    novo->sudoeste = NULL;
    novo->sudeste = NULL;
    return novo;
}

int main(void){
    
}