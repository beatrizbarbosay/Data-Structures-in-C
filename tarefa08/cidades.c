#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    novo->tipo = Interno; //define o tipo
    novo->memoria.interno.noroeste = NULL;
    novo->memoria.interno.nordeste = NULL;
    novo->memoria.interno.sudoeste = NULL;
    novo->memoria.interno.sudeste = NULL;
    return novo;
}

ponteiro criarno_folha(char nome[MAX], int x, int y){
    ponteiro novo = malloc(sizeof(struct arvore));
    novo->tipo = FolhaOcupada; //define o tipo
    strcpy(novo->memoria.folha.nome,nome);
    novo->memoria.folha.x = x;
    novo->memoria.folha.y = y;
    return novo;
}

void buscar(ponteiro mapatotal, int x, int y, int w, int centrox, int centroy){
    if(mapatotal==NULL){ //se percorrer toda a arvore e nao encontrar
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
        return;
    }
    if(mapatotal->tipo == FolhaOcupada){ //se for uma folha ocupada, verifica se as coordenadas sao iguais
        if(mapatotal->memoria.folha.x == x && mapatotal->memoria.folha.y==y){
            printf("Cidade %s encontrada no ponto (%d,%d).\n", mapatotal->memoria.folha.nome, x, y);
        }else{
            printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
        }
        return;
    }

    int tamanho = w/2; //procura o x e y nos quadrantes que eles estao inseridos e faz a busca dos pontos recursivamente
    if (x < centrox && y < centroy) {
        buscar(mapatotal->memoria.interno.sudoeste, x, y, tamanho, centrox-tamanho/2, centroy-tamanho/2); //atualiza para cada vez que divide o quadrante, os valores dos centros
    } else if (x < centrox && y >= centroy) { 
        buscar(mapatotal->memoria.interno.noroeste, x, y, tamanho, centrox-tamanho/2, centroy+tamanho/2);
    } else if (x >= centrox && y < centroy) { 
        buscar(mapatotal->memoria.interno.sudeste, x, y, tamanho, centrox+tamanho/2, centroy-tamanho/2);
    } else { 
        buscar(mapatotal->memoria.interno.nordeste, x, y, tamanho, centrox+tamanho/2, centroy+tamanho/2);
    }
}

void inserir(ponteiro *mapatotal, int x, int y, char nome[MAX],int w, int centrox, int centroy){
    if(*mapatotal== NULL){ //cria o primeiro nó folha
        *mapatotal = criarno_folha(nome,x,y);
        return;
    }

    if((*mapatotal)->tipo== FolhaOcupada){ //condicao folha ocupada
        ponteiro antigafolha = *mapatotal; //salva as informaçoes da antiga cidade
        int xa= antigafolha->memoria.folha.x;
        int ya= antigafolha->memoria.folha.y;
        char nomea[MAX];
        strcpy(nomea,antigafolha->memoria.folha.nome);

        *mapatotal = criarno_interno(); //cria um nó interno para separar em quadrantes

        inserir(mapatotal, xa, ya, nomea, w, centrox, centroy); //coloca a antiga cidade no seu quadrante
        free(antigafolha);
        inserir(mapatotal, x, y, nome, w, centrox, centroy); //coloca a cidade nova no quadrante
        return;
    }

    int tamanho = w/2;
    //para o caso de nao ser uma folha ocupada, insere a cidade em seus respectivos quadrantes
    if (x < centrox && y < centroy) { 
        inserir(&(*mapatotal)->memoria.interno.sudoeste, x, y, nome, tamanho, centrox-tamanho/2, centroy-tamanho/2);
    } else if (x < centrox && y >= centroy) { 
        inserir(&(*mapatotal)->memoria.interno.noroeste, x, y, nome, tamanho, centrox-tamanho/2, centroy+tamanho/2);
    } else if (x >= centrox && y < centroy) {
        inserir(&(*mapatotal)->memoria.interno.sudeste, x, y, nome, tamanho, centrox+tamanho/2, centroy-tamanho/2);
    } else { 
        inserir(&(*mapatotal)->memoria.interno.nordeste, x, y, nome, tamanho, centrox+tamanho/2, centroy+tamanho/2);
    }
}

void remover(ponteiro *mapatotal, int x, int y, int w, int centrox, int centroy){
    if(*mapatotal==NULL){
        return;
    }
    if((*mapatotal)->tipo == FolhaOcupada){  
        if((*mapatotal)->memoria.folha.x==x && (*mapatotal)->memoria.folha.y==y){ //caso encontre uma cidade com as coordenadas a serem removidas
            printf("Cidade %s removida do ponto (%d,%d).\n", (*mapatotal)->memoria.folha.nome, x,y);
            free(*mapatotal);
            *mapatotal=NULL; //remove
            return;
        }
    }
    int tamanho = w / 2;
    //procura a coordenada a ser removida a partir do quadrante em que ela esta e chama recursivamente
    if (x < centrox && y < centroy) {
        remover(&(*mapatotal)->memoria.interno.sudoeste, x, y, tamanho, centrox - tamanho / 2, centroy - tamanho / 2);
    } else if (x < centrox && y >= centroy) { 
        remover(&(*mapatotal)->memoria.interno.noroeste, x, y, tamanho, centrox - tamanho / 2, centroy + tamanho / 2);
    } else if (x >= centrox && y < centroy) { 
        remover(&(*mapatotal)->memoria.interno.sudeste, x, y, tamanho, centrox + tamanho / 2, centroy - tamanho / 2);
    } else { 
        remover(&(*mapatotal)->memoria.interno.nordeste, x, y, tamanho, centrox + tamanho / 2, centroy + tamanho / 2);
    }
}

void raio(ponteiro mapatotal, int r, int x, int y, int w, int centrox, int centroy){
    if(mapatotal == NULL){ //parada da recursao
        return;
    }

    if(mapatotal->tipo == FolhaOcupada){ //compara as coordenadas das folhas ocupadas com o raio
        int distanciax = (mapatotal->memoria.folha.x) - x;
        int distanciay = (mapatotal->memoria.folha.y) - y;
        double distancia = sqrt((distanciax * distanciax) + (distanciay * distanciay)); //para calcular a distancia dos pontos a partir do raio de um circulo

        if(distancia <= r){ //se estiver dentro do raio, printa o nome da cidade
            printf("%s ", mapatotal->memoria.folha.nome);
        }
    }

    int tamanho = w / 2; //chama recursivamente a partir dos quadrantes de interesse
    if (mapatotal->tipo == Interno && x - r <= centrox + tamanho && x + r >= centrox - tamanho && y - r <= centroy + tamanho && y + r >= centroy - tamanho) {
        raio(mapatotal->memoria.interno.noroeste, r, x, y, tamanho, centrox - tamanho / 2, centroy + tamanho / 2);
        raio(mapatotal->memoria.interno.nordeste, r, x, y, tamanho, centrox + tamanho / 2, centroy + tamanho / 2);
        raio(mapatotal->memoria.interno.sudoeste, r, x, y, tamanho, centrox - tamanho / 2, centroy - tamanho / 2);
        raio(mapatotal->memoria.interno.sudeste, r, x, y, tamanho, centrox + tamanho / 2, centroy - tamanho / 2);
    }
}


void liberar_memoria(ponteiro *mapatotal) {
    if (*mapatotal == NULL) {
        return;
    }

    if ((*mapatotal)->tipo == Interno) {
        liberar_memoria(&(*mapatotal)->memoria.interno.noroeste);
        liberar_memoria(&(*mapatotal)->memoria.interno.nordeste);
        liberar_memoria(&(*mapatotal)->memoria.interno.sudoeste);
        liberar_memoria(&(*mapatotal)->memoria.interno.sudeste);
    }

    free(*mapatotal);
    *mapatotal= NULL;
}


int main(void){
    ponteiro mapatotal = NULL;
    int w=0;
    scanf("%d", &w);
    int centrox= w/2; //para usar no calculo das coordenadas dos quadrantes
    int centroy= w/2;
    while(1){
        char comando;
        scanf("%c", &comando);
        if(comando == 's'){
            printf("Sistema encerrado.");
            liberar_memoria(&mapatotal);
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
            printf("Cidades a distancia %d de (%d,%d): ", r, xo, yo);
            raio(mapatotal,r,xo,yo,w,centrox,centroy);
            printf("\n");
        }
    }
}