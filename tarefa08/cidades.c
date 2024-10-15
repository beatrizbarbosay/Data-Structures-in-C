#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef enum {Interno, FolhaVazia, FolhaOcupada} TipoNo;

typedef struct arvore *ponteiro;

struct arvore { 
    TipoNo tipo;
    union{
        struct{
            ponteiro noroeste;
            ponteiro nordeste;
            ponteiro sudoeste;
            ponteiro sudeste;
        }interno;
        struct{
            char nome[MAX];
            int x;
            int y;
        }folha;
    }memoria;
};

ponteiro criarno_interno() { 
    ponteiro novo =  malloc(sizeof(struct arvore));
    novo->tipo = Interno;
    novo->memoria.interno.noroeste = NULL;
    novo->memoria.interno.nordeste = NULL;
    novo->memoria.interno.sudoeste = NULL;
    novo->memoria.interno.sudeste = NULL;
    return novo;
}

ponteiro criarno_folha(char nome[MAX], int x, int y){
    ponteiro novo = malloc(sizeof(struct arvore));
    novo->tipo = FolhaOcupada;
    strcpy(novo->memoria.folha.nome,nome);
    novo->memoria.folha.x = x;
    novo->memoria.folha.y = y;
    return novo;
}

ponteiro criarno_vazia(){
    ponteiro novo = malloc(sizeof(struct arvore));
    novo->tipo = FolhaVazia;
    return novo;
}

void buscar(ponteiro *mapatotal){

}
void inserir(ponteiro *mapatotal, int x, int y, char nome[MAX],int w, int centrox, int centroy){
    if(*mapatotal== NULL){ //cria o primeiro nó folha
        *mapatotal = criarno_folha(nome,x,y);
        return;
    }

    if((*mapatotal)->tipo== FolhaOcupada){ //condicao folha ocupada
        ponteiro antigafolha = *mapatotal;
        int xa= antigafolha->memoria.folha.x;
        int ya= antigafolha->memoria.folha.y;
        char nomea[MAX];
        strcpy(nomea,antigafolha->memoria.folha.nome);

        *mapatotal = criarno_interno();

        inserir(mapatotal, xa, ya, nomea, w, centrox, centroy);
        inserir(mapatotal, x, y, nome, w, centrox, centroy);
        return;
    }

    int tamanho = w/2;

    if (x < centrox && y < centroy) { // Sudoeste
        inserir(&(*mapatotal)->memoria.interno.sudoeste, x, y, nome, tamanho, centrox-tamanho/2, centroy-tamanho/2);
    } else if (x < centrox && y >= centroy) { // Noroeste
        inserir(&(*mapatotal)->memoria.interno.noroeste, x, y, nome, tamanho, centrox-tamanho/2, centroy+tamanho/2);
    } else if (x >= centrox && y < centroy) { // Sudeste
        inserir(&(*mapatotal)->memoria.interno.sudeste, x, y, nome, tamanho, centrox+tamanho/2, centroy-tamanho/2);
    } else { // Nordeste
        inserir(&(*mapatotal)->memoria.interno.nordeste, x, y, nome, tamanho, centrox+tamanho/2, centroy+tamanho/2);
    }
}


void imprimir_arvore(ponteiro no, int nivel) {
    if (no == NULL) {
        printf("%*sV\n", nivel * 4, ""); // Imprime V para nó vazio
        return;
    }
    
    if (no->tipo == Interno) {
        printf("%*sI\n", nivel * 4, ""); // Imprime I para nó interno
        imprimir_arvore(no->memoria.interno.noroeste, nivel + 1);
        imprimir_arvore(no->memoria.interno.nordeste, nivel + 1);
        imprimir_arvore(no->memoria.interno.sudoeste, nivel + 1);
        imprimir_arvore(no->memoria.interno.sudeste, nivel + 1);
    } else if (no->tipo == FolhaOcupada) {
        printf("%*sCidade %s (%d, %d)\n", nivel * 4, "", no->memoria.folha.nome, no->memoria.folha.x, no->memoria.folha.y);
    }
}


int main(void){
    ponteiro mapatotal = criarno_interno();
    int w=0;
    scanf("%d", &w);
    int centrox= w/2;
    int centroy= w/2;
    while(1){
        char comando;
        scanf("%c", &comando);
        if(comando == 's'){
            printf("Sistema encerrado.");
            return 0;
        }else if(comando == 'i'){
            int x, y;
            char nome[MAX];
            scanf("%d %d %s", &x, &y, nome);
            inserir(&mapatotal, x, y, nome, w, centrox, centroy);
        }else if(comando=='b'){
            int xb, yb;
            scanf("%d %d", &xb, &yb);
            //funcao buscar
        }else if(comando == 'r'){
            int xr, yr;
            scanf("%d %d", &xr, &yr);
            //funcao remover
        }else if(comando == 'o'){
            int r, xo, yo;
            scanf("%d %d %d", &r, &xo, &yo);
            //funcao buscar
        }
        else if(comando == 'p'){
            imprimir_arvore(mapatotal, 0);

        }
    }
}