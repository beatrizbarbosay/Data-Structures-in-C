#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct no *ponteiro; //ponteiro para a estrutura
struct no { //estrututa que representa cada nó da lista ligadada
    char nucleo;
    ponteiro prox;
};

typedef struct lista{ //lista ligada dos nucleos
    ponteiro inicio;
} lista;

void inserir(lista *sequencia, char caractere, int posicao){ 
    ponteiro novo=malloc(sizeof(struct no)); //cria um novo nó
    novo->nucleo = caractere; //atribui o caractere
    novo->prox= NULL; //inicializa o nó

    if(posicao!=0){
        ponteiro atual = sequencia->inicio; //cria um ponteiro auxiliar para percorrer a lista 
        int i=0;
        while(atual!= NULL && i<posicao-1){ //coloca o nó "atual" na posicao desejada
            atual= atual-> prox;
            i++;
        }
        novo->prox = atual->prox; //adiciona o novo elemento na posicao correta
        atual->prox =novo;
    }else{ //se a posicao for 0, o novo será o primeiro
        novo->prox = sequencia->inicio;
        sequencia->inicio= novo;
    }
    printf("%c inserido em %d\n", novo->nucleo, posicao);
}

void remover(lista *sequencia, int posicao){
    ponteiro atual = sequencia -> inicio; //cria dois nós auxiliares
    ponteiro antecessor= NULL;
    if(posicao==0){
        sequencia->inicio = atual->prox; //se for pra remover o primeiro, torna o segundo da lista o primeiro
    }else{ //para outros valores da posicao
        for(int i=0; i<posicao && atual!=NULL; i++){ //percorre a lista ate encontrar o nó na posicao desejada
            antecessor=atual;
            atual= atual->prox;
            if(i==posicao-1){ //encontrou a posicao
                antecessor->prox = atual->prox; //remove 
            }          
        }
    }
    printf("%c removido de %d\n", atual->nucleo, posicao); 
    free(atual);
}

void imprimir(lista *sequencia){
    for(ponteiro atual=sequencia->inicio; atual !=NULL; atual = atual->prox){
        printf("%c ", atual->nucleo);
    }
}


int main(void){
    lista *sequencia= malloc(sizeof(lista));
    sequencia->inicio=NULL; //inicializa a lista vazia
    char comando[MAX];
    while(1){
        scanf("%s", comando);
        if(strcmp(comando, "sair")==0){
            break;
        }
        if(strcmp(comando, "inserir")==0){
            char caractere;
            int posicao=0;
            scanf(" %c %d",&caractere, &posicao);
            inserir(sequencia, caractere, posicao);
        }
        if(strcmp(comando,"remover")==0){
            int posremover =0;
            scanf("%d", &posremover);
            remover(sequencia, posremover);
        }
        if(strcmp(comando,"inverter-prefixo")==0){
            
        }
        if(strcmp(comando,"inverter-sufixo")==0){
            
        }
        if(strcmp(comando,"transpor")==0){
            
        }
        if(strcmp(comando,"imprimir")==0){
            imprimir(sequencia);
            
        }
    }
    free(sequencia);
    return 0;
}