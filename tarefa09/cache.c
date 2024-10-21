#include <stdio.h>
#include <stdlib.h>  
#include <limits.h>

typedef struct{ 
    int numero;
    int prioridade;
}objeto;

typedef struct{
    objeto *vetor;
    int quantidade;
    int cachetam;
} heap;

typedef heap *ponteiro;

ponteiro criar_heap(int cachetam){
    ponteiro cache = malloc(sizeof(heap));
    cache->vetor = malloc(cachetam*(sizeof(objeto)));
    cache->quantidade = 0;
    cache->cachetam = cachetam;
    return cache;
}
void calcular_prioridade(objeto *comprioridade, int sequencia[], int seqtam){
    for(int i=0; i<seqtam; i++){
        comprioridade[i].numero = sequencia[i];
        comprioridade[i].prioridade = __INT_MAX__;

        for(int j = i+1; j<seqtam; j++){
            if(sequencia[j]==comprioridade[i].numero){
                comprioridade[i].prioridade = j;
                break;
            }
        }
    }
} 

int main(void){
    int cachetam; //tamanho do cache
    int objetos;
    int seqtam; //tamanho da sequencia
    scanf("%d %d %d", &cachetam, &objetos, &seqtam);

    int *sequencia = malloc(seqtam*sizeof(int));
    for(int i=0; i<seqtam; i++){
        scanf("%d", &sequencia[i]);
    }

    objeto *comprioridade = malloc(seqtam*sizeof(objeto));

    calcular_prioridade(comprioridade, sequencia, seqtam);

    for (int i = 0; i < seqtam; i++) {
        printf("Objeto: %d, Prioridade: %d\n", comprioridade[i].numero, comprioridade[i].prioridade);
    }

    ponteiro cache = criar_heap(cachetam);
    free(sequencia);
    free(comprioridade);

    return 0;
    //funcao inserir no heap
}