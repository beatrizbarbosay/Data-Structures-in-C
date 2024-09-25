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
}

void inserir_printar(lista *sequencia, char caractere, int posicao){ 
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
    free(atual);
}

void remover_printar(lista *sequencia, int posicao){
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

void printar_prefixo(lista *sequencia, int posicao){
    ponteiro atual= sequencia->inicio;
    int i=0;
    while(atual!=NULL && i<posicao){
        printf("%c ", atual->nucleo);
        atual= atual->prox;
        i++;
    }
}

void inverter_prefixo(lista *sequencia, int posicao){
    ponteiro atual = sequencia->inicio; //cria 3 ponteiros auxiliares
    ponteiro antecessor= NULL;
    ponteiro sucessor= NULL;
    int i=0;
    while(atual!=NULL && i<posicao){ //percorre ate a posicao que é pra inverter
        sucessor= atual->prox; //define o sucessor do atual
        atual->prox= antecessor; //atual aponta pro antecessor
        antecessor= atual; //atualiza o antecessor
        atual= sucessor; //atualiza o sucessor
        i++;
    }
    sequencia->inicio->prox=atual; //conecta com o resto da lista
    sequencia->inicio= antecessor; //atualiza o novo inicio
}

void printar_sufixo(lista *sequencia, int posicao){
    ponteiro atual= sequencia->inicio;
    char nucleos[MAX];
    int i=0;
    while(atual!=NULL){
        nucleos[i]= atual->nucleo;
        atual= atual->prox;
        i++;
    }
    for(int j= i-posicao; j<i; j++){
        printf("%c ", nucleos[j]);
    }
}

void inverter_sufixo(lista *sequencia, int posicao){
    ponteiro atual= sequencia->inicio;
    int tamanho=0;
    while(atual !=NULL){
        atual= atual->prox;
        tamanho++;
    }
    int comecar = tamanho - posicao;
    atual = sequencia->inicio; //cria 3 ponteiros auxiliares
    ponteiro antecessor= NULL;
    ponteiro sucessor= NULL;

    for(int i=0; i<comecar; i++){
        antecessor=atual;
        atual= atual->prox;
    }
    ponteiro inicio2 = atual;
    for(int i=0; i<posicao; i++){ //percorre ate a posicao que é pra inverter
        sucessor= atual->prox; //define o sucessor do atual
        atual->prox= antecessor; //atual aponta pro antecessor
        antecessor= atual; //atualiza o antecessor
        atual= sucessor; //atualiza o sucessor
    }
    if(comecar==0){
        sequencia->inicio = antecessor;
    }else{
        ponteiro invertida = sequencia->inicio;
        for(int i=0; i<comecar-1; i++){
            invertida= invertida->prox;
        }
        invertida->prox = antecessor;
    }
    inicio2->prox= atual;
}

void transpor(lista *sequencia, int inicio, int fim, int posicoes){
    int i=0;
    int j=0;
    char nucleos[MAX];
    ponteiro atual= sequencia->inicio;
    while(atual!=NULL && i<inicio){ //guarda numa lista os caracteres a serem transpostos
        atual= atual->prox;
        i++;
    }
    while(atual!=NULL && i<=fim){
        nucleos[j]= atual-> nucleo;
        atual = atual->prox;
        j++;
        i++;
    }

    if(posicoes<0){
        printf("subsequencia ");
        for(int i=0; i<fim-inicio+1; i++){
            printf("%c ", nucleos[i]);
        }
        printf("<< %d", -posicoes);
    }

    if(posicoes>0){
        printf("subsequencia ");
        for(int i=0; i<fim-inicio+1; i++){
            printf("%c ", nucleos[i]);
        }
        printf(">> %d", posicoes);
    }

    for(int k=fim; k>=inicio; k--){
        remover(sequencia, k);
    }
    int posicao2 = inicio+posicoes;
    if(posicao2<0){
        posicao2=0;
    }
    ponteiro auxiliar= sequencia->inicio;
    int m=0;
    while(auxiliar!=NULL && m<posicao2){
        auxiliar=auxiliar->prox;
        i++;
    }
    for(int k=0; k<j;k++){
        inserir(sequencia, nucleos[k], posicao2+k);
    }
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
            inserir_printar(sequencia, caractere, posicao);
        }
        if(strcmp(comando,"remover")==0){
            int posremover =0;
            scanf("%d", &posremover);
            remover_printar(sequencia, posremover);
        }
        if(strcmp(comando,"inverter-prefixo")==0){
            int prefixo=0;
            scanf("%d", &prefixo);
            printf("prefixo ");
            printar_prefixo(sequencia, prefixo);
            printf("-> ");
            inverter_prefixo(sequencia, prefixo); 
            printar_prefixo(sequencia,prefixo);
        }
        if(strcmp(comando,"inverter-sufixo")==0){
            int sufixo=0;
            scanf("%d", &sufixo);
            printf("sufixo ");
            printar_sufixo(sequencia, sufixo);
            printf("-> ");
            inverter_sufixo(sequencia, sufixo);
            printar_sufixo(sequencia, sufixo); 
        }
        if(strcmp(comando,"transpor")==0){
            int inicio,final,posicoes=0;
            scanf("%d %d %d", &inicio, &final, &posicoes);     
            transpor(sequencia, inicio, final, posicoes);     
        }
        if(strcmp(comando,"imprimir")==0){
            printf("sequencia ");
            imprimir(sequencia);
            
        }
    }
    free(sequencia);
    return 0;
}