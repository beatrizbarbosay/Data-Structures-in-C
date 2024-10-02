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
} lista;

void adicionarpedaco(lista*cobrainteira, char**matriz, int linhacobra, int colunacobra){
    ponteiro pedaco = (ponteiro)malloc(sizeof(struct cobra)); //a nova cabeca da cobra vai ter as coordenadas da cabeca anterior
    pedaco->posicaolinha= linhacobra;
    pedaco->posicaocoluna= colunacobra;
    pedaco->prox= cobrainteira->cabeca;
    pedaco->anterior = NULL;

    if(cobrainteira->cabeca!=NULL){ //para crescer a cobra
        cobrainteira->cabeca->anterior = pedaco;
    }
    cobrainteira->cabeca = pedaco; //define o nó inicial como cabeça da cobra
    matriz[linhacobra][colunacobra]='#';
}


void printarmatriz(char **matriz,int linham, int colunam){
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}
void movercobra(lista*cobrainteira, int linham, int colunam){
    ponteiro atual = cobrainteira->cabeca;
    while(atual!=NULL){ //move todo o corpo de forma que cada nó siga a posicao do nó anterior
        atual->posicaolinha= atual->anterior->posicaolinha; 
        atual->posicaocoluna= atual->anterior->posicaocoluna;
        atual=atual->prox;
    }
}

void atualizarmatriz(char **matriz,int linham, int colunam, lista *cobrainteira){ //atualiza a  matriz a cada movimento
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            if(matriz[i][j] != '*'){
                matriz[i][j]= '_';
            }
        }
    }
    ponteiro atual = cobrainteira->cabeca;
    while(atual!=NULL){
        matriz[atual->posicaolinha][atual->posicaocoluna]='#';
        atual= atual->prox;
    }
}

_Bool youwin(char **matriz, int linham, int colunam){ //verifica se a cobra ocupa toda a matriz
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            if(matriz[i][j]!='#'){
                return 0;
            }
        }
    }
    return 1;
}

void youlose(lista*cobrainteira){ //checa se a posicao da cabeca coincide com a posicao de qualquer outra parte do corpo
    ponteiro atual = cobrainteira->cabeca->prox;
    int cabecalinha = cobrainteira->cabeca->posicaolinha;
    int cabecacoluna= cobrainteira->cabeca->posicaocoluna;

    while(atual!=NULL){
        if(atual->posicaolinha == cabecalinha && atual->posicaocoluna == cabecacoluna){
            printf("YOU LOSE");
        }
        atual = atual->prox;
    }
}

void limitelinha(lista*cobrainteira, int linham, int colunam){ //funcao caso a cobra ultrasse as bordas da linha
     if (cobrainteira->cabeca->posicaolinha < 0) {
        cobrainteira->cabeca->posicaolinha = linham - 1;  // vai para a última linha
    } else if (cobrainteira->cabeca->posicaolinha >= linham) {
        cobrainteira->cabeca->posicaolinha = 0;  // vai para a primeira linha
    }   
}

void limitecoluna(lista*cobrainteira, int linham, int colunam){ //funcao caso a cobra ultrapasse as bordas da coluna
    if (cobrainteira->cabeca->posicaocoluna < 0) {
        cobrainteira->cabeca->posicaocoluna = colunam - 1; 
    } else if (cobrainteira->cabeca->posicaocoluna >= colunam) {
        cobrainteira->cabeca->posicaocoluna = 0; 
    }
}


int main(void){
    lista *cobrainteira= malloc(sizeof(lista)); //inicializa a lista ligada que representará a cobra
    cobrainteira->cabeca=NULL;

    int linham=0;
    int colunam=0;
    char inicial[MAX];
    scanf("%s %d %d", inicial, &linham, &colunam);//aloca e inicializa a matriz
    char**matriz=(char**)malloc(linham*sizeof(char*));
    for(int i=0; i<linham; i++){
        matriz[i]=(char*)malloc(colunam*sizeof(char));
    }
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            matriz[i][j]='_';
        }
    }

    int linhacobra=0; //coloca a cobra no lugar inicial
    int colunacobra=0;
    scanf("%s %d %d", inicial, &linhacobra, &colunacobra);
    adicionarpedaco(cobrainteira, matriz, linhacobra, colunacobra);

    while(1){
        char comando[MAX];
        scanf("%s", comando);
        int linhafruta=0;
        int colunafruta=0;
        if(strcmp(comando,"FRUTA")==0){
            scanf("%d %d",&linhafruta, &colunafruta);
            matriz[linhafruta][colunafruta]='*';
            printarmatriz(matriz, linham, colunam);
            continue;
        }
        if(strcmp(comando,"w")==0){
            cobrainteira->cabeca->posicaolinha-= 1;
            limitelinha(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"s")==0){
            cobrainteira->cabeca->posicaolinha +=1;
            limitelinha(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"a")==0){
            cobrainteira->cabeca->posicaocoluna -=1;
            limitecoluna(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"d")==0){
            cobrainteira->cabeca->posicaocoluna+=1;
            limitecoluna(cobrainteira, linham, colunam);
        }

        if(cobrainteira->cabeca->posicaocoluna==colunafruta && cobrainteira->cabeca->posicaolinha==linhafruta){
            matriz[linhafruta][colunafruta]='#';
            adicionarpedaco(cobrainteira, matriz, linhafruta, colunafruta);
        }
        movercobra(cobrainteira, linham, colunam);
        atualizarmatriz(matriz,linham, colunam, cobrainteira);
        printarmatriz(matriz,linham,colunam);
        youlose(cobrainteira);
        if(youwin(matriz,linham,colunam)){
            printf("YOU WIN");
            return 0;
        }
    }    
}   