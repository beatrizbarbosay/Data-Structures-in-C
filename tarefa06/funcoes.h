#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct cobra *ponteiro; 
struct cobra { //nós de cada pedaço da cobra
    int posicaolinha;
    int posicaocoluna;
    ponteiro prox;
    ponteiro anterior;
};

typedef struct lista{ //cabeça da cobra
    ponteiro cabeca;
    int tamanho;
} lista;

void adicionarpedaco(lista*cobrainteira, char**matriz, int linhacobra, int colunacobra);
void comeufruta(lista*cobrainteira, char**matriz, int linhacobra, int colunacobra);
void printarmatriz(char **matriz,int linham, int colunam);
void movercobra(lista*cobrainteira, int linhacobra, int colunacobra);
void atualizarmatriz(char **matriz,int linham, int colunam, lista *cobrainteira);
int youwin(char **matriz, int linham, int colunam);
int youlose(lista*cobrainteira);
void limitelinha(lista*cobrainteira, int linham, int colunam);
void limitecoluna(lista*cobrainteira, int linham, int colunam);
void freecobra(lista*cobrainteira);
void freematriz(char**matriz, int linham, int colunam);
