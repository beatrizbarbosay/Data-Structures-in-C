#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef enum {Interno, FolhaVazia, FolhaOcupada} TipoNo; //3 tipos diferentes de nós

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

void buscar(ponteiro mapatotal, int x, int y, int w, int centrox, int centroy){
    if(mapatotal==NULL){
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
        return;
    }
    if(mapatotal->tipo == FolhaOcupada){
        if(mapatotal->memoria.folha.x == x && mapatotal->memoria.folha.y==y){
            printf("Cidade %s encontrada no ponto (%d,%d).\n", mapatotal->memoria.folha.nome, x, y);
        }else{
            printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
        }
        return;
    }

    int tamanho = w/2;
    if (x < centrox && y < centroy) {
        buscar(mapatotal->memoria.interno.sudoeste, x, y, tamanho, centrox-tamanho/2, centroy-tamanho/2);
    } else if (x < centrox && y >= centroy) { 
        buscar(mapatotal->memoria.interno.noroeste, x, y, tamanho, centrox-tamanho/2, centroy+tamanho/2);
    } else if (x >= centrox && y < centroy) { 
        buscar(mapatotal->memoria.interno.sudeste, x, y, tamanho, centrox+tamanho/2, centroy-tamanho/2);
    } else { // Nordeste
        buscar(mapatotal->memoria.interno.nordeste, x, y, tamanho, centrox+tamanho/2, centroy+tamanho/2);
    }
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

void remover(ponteiro *mapatotal, int x, int y, int w, int centrox, int centroy){
    if(*mapatotal==NULL){
        return;
    }
    if((*mapatotal)->tipo == FolhaOcupada){
        if((*mapatotal)->memoria.folha.x==x && (*mapatotal)->memoria.folha.y==y){
            printf("Cidade %s removida do ponto (%d,%d).\n", (*mapatotal)->memoria.folha.nome, x,y);
            free(*mapatotal);
            *mapatotal=NULL;
            return;
        }
    }
    int tamanho = w / 2;

    if (x < centrox && y < centroy) {
        remover(&(*mapatotal)->memoria.interno.sudoeste, x, y, tamanho, centrox - tamanho / 2, centroy - tamanho / 2);
    } else if (x < centrox && y >= centroy) { 
        remover(&(*mapatotal)->memoria.interno.noroeste, x, y, tamanho, centrox - tamanho / 2, centroy + tamanho / 2);
    } else if (x >= centrox && y < centroy) { 
        remover(&(*mapatotal)->memoria.interno.sudeste, x, y, tamanho, centrox + tamanho / 2, centroy - tamanho / 2);
    } else { 
        remover(&(*mapatotal)->memoria.interno.nordeste, x, y, tamanho, centrox + tamanho / 2, centroy + tamanho / 2);
    }

    if((*mapatotal)->tipo == Interno){
        int cidades =0;
        ponteiro antigafolha = NULL;
        if((*mapatotal)->memoria.interno.noroeste!=NULL && (*mapatotal)->memoria.interno.noroeste->tipo== FolhaOcupada){
            cidades++;
            antigafolha = (*mapatotal)->memoria.interno.noroeste;
        }
        if((*mapatotal)->memoria.interno.nordeste!=NULL && (*mapatotal)->memoria.interno.nordeste->tipo== FolhaOcupada){
            cidades++;
            antigafolha = (*mapatotal)->memoria.interno.nordeste;
        }
        if((*mapatotal)->memoria.interno.sudeste!=NULL && (*mapatotal)->memoria.interno.sudeste->tipo== FolhaOcupada){
            cidades++;
            antigafolha = (*mapatotal)->memoria.interno.sudeste;
        }
        if((*mapatotal)->memoria.interno.sudoeste!=NULL && (*mapatotal)->memoria.interno.sudoeste->tipo== FolhaOcupada){
            cidades++;
            antigafolha = (*mapatotal)->memoria.interno.sudoeste;
        }

        if(cidades==1){
            ponteiro novafolha= criarno_folha(antigafolha->memoria.folha.nome, antigafolha->memoria.folha.x, antigafolha->memoria.folha.y);
            free(*mapatotal);
            *mapatotal = novafolha;
        }
    }
}

#include <math.h>

void raio(ponteiro mapatotal, int r, int x, int y, int w, int centrox, int centroy){
    if(mapatotal == NULL){
        return;
    }

    if(mapatotal->tipo == FolhaOcupada){
        int distanciax = (mapatotal->memoria.folha.x) - x;
        int distanciay = (mapatotal->memoria.folha.y) - y;
        double distancia = sqrt((distanciax * distanciax) + (distanciay * distanciay));

        if(distancia <= r){
            printf("%s ", mapatotal->memoria.folha.nome);
        }
    }

    int tamanho = w / 2;
    if (mapatotal->tipo == Interno && x - r <= centrox + tamanho && x + r >= centrox - tamanho && y - r <= centroy + tamanho && y + r >= centroy - tamanho) {
        raio(mapatotal->memoria.interno.noroeste, r, x, y, tamanho, centrox - tamanho / 2, centroy + tamanho / 2);
        raio(mapatotal->memoria.interno.nordeste, r, x, y, tamanho, centrox + tamanho / 2, centroy + tamanho / 2);
        raio(mapatotal->memoria.interno.sudoeste, r, x, y, tamanho, centrox - tamanho / 2, centroy - tamanho / 2);
        raio(mapatotal->memoria.interno.sudeste, r, x, y, tamanho, centrox + tamanho / 2, centroy - tamanho / 2);
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
            printf("Cidade %s inserida no ponto (%d,%d).\n", nome, x, y);
        }else if(comando=='b'){
            int xb, yb;
            scanf("%d %d", &xb, &yb);
            buscar(mapatotal, xb, yb,w, centrox, centroy);
        }else if(comando == 'r'){
            int xr, yr;
            scanf("%d %d", &xr, &yr);
            remover(&mapatotal, xr, yr, w, centrox, centroy);
        }else if(comando == 'o'){
            int r, xo, yo;
            scanf("%d %d %d", &xo, &yo, &r);
            //funcao buscar
            printf("Cidades a distancia %d de (%d,%d): ", r, xo, yo);
            raio(mapatotal,r,xo,yo,w,centrox,centroy);
            printf("\n");
        }

        else if(comando == 'p'){
            imprimir_arvore(mapatotal, 0);

        }
    }
}