#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct no *ponteiro; //ponteiro para a estrutura
struct no { //estrututa que representa cada nó da lista ligadada
    char nucleo;
    ponteiro prox;
};

typedef struct lista{ //lista ligada dos nucleos
    ponteiro inicio;
} lista;

void inserir(lista *sequencia, char caractere, int posicao){ //insercao sem print para usar essa funcao no comando "transpor"depois
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

void inserir_printar(lista *sequencia, char caractere, int posicao){ //insercao com print
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
    char nucleos[MAX]; //cria um vetor auxiliar para armazenar os nucleos
    int i=0;
    while(atual!=NULL){
        nucleos[i]= atual->nucleo;
        atual= atual->prox;
        i++;
    }
    for(int j= i-posicao; j<i; j++){ //printa de tras pra frente
        printf("%c ", nucleos[j]);
    }
}

void inverter_sufixo(lista *sequencia, int posicao){
    ponteiro atual= sequencia->inicio;
    int tamanho=0;
    while(atual !=NULL){ //encontra o tamanho da lista
        atual= atual->prox;
        tamanho++;
    }
    int comecar = tamanho - posicao; //a partir da onde começa a inverter
    atual = sequencia->inicio; //redefine atual
    ponteiro antecessor= NULL; //cria mais 2 ponteiros auxiliares
    ponteiro sucessor= NULL;

    for(int i=0; i<comecar; i++){ //percorre a lista ate onde é pra começar a inverter
        antecessor=atual;
        atual= atual->prox;
    }
    ponteiro inicio2 = atual; //aponta para o inicio da inversao
    for(int i=0; i<posicao; i++){ //percorre ate a posicao que é pra inverter
        sucessor= atual->prox; //define o sucessor do atual
        atual->prox= antecessor; //atual aponta pro antecessor
        antecessor= atual; //atualiza o antecessor
        atual= sucessor; //atualiza o sucessor
    }
    if(comecar==0){ //reconecta a lista se a inversao comecar no inico
        sequencia->inicio = antecessor;
    }else{ //reconecta a lista para outros casos
        ponteiro invertida = sequencia->inicio; 
        for(int i=0; i<comecar-1; i++){ //percorre ate o inicio da inversao
            invertida= invertida->prox; 
        }
        invertida->prox = antecessor; //o nó anterior ao comeco da inversao agora aponta para o primeiro elemento invertido
    }
    inicio2->prox= atual; //aponta para o primeiro elemento após inversao
}

void transpor(lista *sequencia, int inicio, int fim, int posicoes){
    int i=0;
    int j=0;
    char nucleos[MAX]; //cria uma lista para armazenar os nucleos que serao transpostos
    ponteiro atual= sequencia->inicio;
    while(atual!=NULL && i<inicio){ //coloca atual na posicao "inicio"
        atual= atual->prox;
        i++;
    }
    while(atual!=NULL && i<=fim){ //armazena os nucleos na lista
        nucleos[j]= atual-> nucleo;
        atual = atual->prox;
        j++;
        i++;
    }

    if(posicoes<0){ //printa para casos positivos
        printf("subsequencia ");
        for(int i=0; i<fim-inicio+1; i++){
            printf("%c ", nucleos[i]);
        }
        printf("<< %d", -posicoes);
    }

    if(posicoes>0){ //printa para casos negativos
        printf("subsequencia ");
        for(int i=0; i<fim-inicio+1; i++){
            printf("%c ", nucleos[i]);
        }
        printf(">> %d", posicoes);
    }

    for(int k=fim; k>=inicio; k--){ //remove os nós especificados da sequencia
        remover(sequencia, k);
    }
    int posicao2 = inicio+posicoes; //posicao a partir da onde os nucleos serao transpostos
    if(posicao2<0){ //garante que nao seja negativo
        posicao2=0;
    }
    ponteiro auxiliar= sequencia->inicio;
    int m=0;
    while(auxiliar!=NULL && m<posicao2){ //avança até a posicao para comecar a transpor
        auxiliar=auxiliar->prox;
        i++;
    }
    for(int k=0; k<j;k++){
        inserir(sequencia, nucleos[k], posicao2+k); //insere novamente os nucleos na sequencia na posicao correta
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
            printf("\n");
    
        }
        if(strcmp(comando,"inverter-sufixo")==0){
            int sufixo=0;
            scanf("%d", &sufixo);
            printf("sufixo ");
            printar_sufixo(sequencia, sufixo);
            printf("-> ");
            inverter_sufixo(sequencia, sufixo);
            printar_sufixo(sequencia, sufixo); 
         printf("\n");
        }
        if(strcmp(comando,"transpor")==0){
            int inicio,final,posicoes=0;
            scanf("%d %d %d", &inicio, &final, &posicoes);     
            transpor(sequencia, inicio, final, posicoes);   
            printf("\n");  
        }
        if(strcmp(comando,"imprimir")==0){
            printf("sequencia ");
            imprimir(sequencia);
            printf("\n");
            
        }
    }
    free(sequencia);
    return 0;
}