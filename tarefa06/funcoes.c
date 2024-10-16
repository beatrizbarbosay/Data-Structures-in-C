#include "funcoes.h"

void adicionarpedaco(lista*cobrainteira, char**matriz, int linhacobra, int colunacobra){ //funcao para inicilizar a cobra no jogo
    ponteiro pedaco = malloc(sizeof(struct cobra)); 
    pedaco->posicaolinha= linhacobra;
    pedaco->posicaocoluna= colunacobra;
    pedaco->prox= cobrainteira->cabeca;
    pedaco->anterior = NULL;
    cobrainteira->cabeca = pedaco; //define o nó como cabeça da cobra
    matriz[linhacobra][colunacobra]='#'; //atualiza valor na matriz
}

void comeufruta(lista*cobrainteira, char**matriz, int linhacobra, int colunacobra){ //adiciona um novo nó no final da cobra, com as coordenadas do nó anterior
    ponteiro atual= cobrainteira->cabeca;

    while(atual->prox !=NULL){ //encontra o ultimo nó
        atual= atual->prox;
    }
    ponteiro novo = malloc(sizeof(struct cobra)); //adiciona um novo no ultimo
    if(cobrainteira->cabeca->prox==NULL){ //caso a cobra só tenha 1 pedaço, o novo nó irá para a posicao que a cabeca da cobra estava
        novo->posicaolinha = linhacobra;
        novo->posicaocoluna = colunacobra;
        novo->prox = NULL; 
        novo->anterior = atual;
        atual->prox = novo;
    }else{ //caso contrario, vai para a posicao do rabo da cobra
        novo->posicaolinha = atual->posicaolinha;
        novo->posicaocoluna = atual->posicaocoluna;
        novo->prox = NULL; 
        novo->anterior = atual;
        atual->prox = novo;
    }

    matriz[novo->posicaolinha][novo->posicaocoluna]='#';
}    



void printarmatriz(char **matriz,int linham, int colunam){
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

void movercobra(lista*cobrainteira, int linhacobra, int colunacobra){
    ponteiro atual = cobrainteira->cabeca->prox;
    int iniciolinha= linhacobra; //guarda a posicao da cabeca da cobra
    int iniciocoluna=colunacobra;
    int anteriorlinha=0;
    int anteriorcoluna=0;

    while(atual!=NULL){ //move a cobra para que cada nó agora aponte para onde estava o nó anterior
        anteriorlinha = atual->posicaolinha;
        anteriorcoluna= atual->posicaocoluna;
        atual->posicaolinha = iniciolinha;
        atual->posicaocoluna= iniciocoluna;
        iniciolinha = anteriorlinha;
        iniciocoluna= anteriorcoluna;
        atual= atual->prox;
    }
}

void atualizarmatriz(char **matriz,int linham, int colunam, lista *cobrainteira){ //atualiza a  matriz a cada movimento
    for(int i=0; i<linham; i++){ //reseta a matriz deixando só onde tem fruta
        for(int j=0; j<colunam; j++){
            if(matriz[i][j] != '*'){
                matriz[i][j]= '_';
            }
        }
    }
    ponteiro atual = cobrainteira->cabeca;
    while(atual!=NULL){ //coloca a cobra nas novas posicoes na matriz
        matriz[atual->posicaolinha][atual->posicaocoluna]='#';
        atual= atual->prox;
    }
}

int youwin(char **matriz, int linham, int colunam){ //verifica se a cobra ocupa toda a matriz
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            if(matriz[i][j]!='#'){
                return 0;
            }
        }
    }
    return 1;
}

int youlose(lista*cobrainteira){ //checa se a posicao da cabeca coincide com a posicao de qualquer outra parte do corpo
    if(cobrainteira->cabeca==NULL || cobrainteira->cabeca->prox==NULL){ //para o caso que a cobra só tenha 1 pedaco
        return 0;
    }
    ponteiro atual = cobrainteira->cabeca->prox;
    int cabecalinha = cobrainteira->cabeca->posicaolinha;
    int cabecacoluna= cobrainteira->cabeca->posicaocoluna;

    while(atual!=NULL){
        if(atual->posicaolinha == cabecalinha && atual->posicaocoluna == cabecacoluna){ //se a cabeca bater em alguma parte do corpo
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
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

void freecobra(lista*cobrainteira){ //funcao para liberar memoria da cobra
    ponteiro atual = cobrainteira->cabeca;
    while(atual!= NULL){
        ponteiro liberar = atual;
        atual = atual->prox;
        free(liberar);
    }
}

void freematriz(char**matriz, int linham, int colunam){ //libera matriz
    for(int i=0; i<linham; i++){
        free(matriz[i]);
    }
    free(matriz);
}