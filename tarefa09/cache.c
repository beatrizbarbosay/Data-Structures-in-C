#include <stdio.h>
#include <stdlib.h>  
#include <limits.h>

typedef struct{ //estrutura de cada objeto do cache
    int numero;
    int prioridade;
}objeto;

typedef struct{ //estrutura para o heap que vai armazenar os objetos
    objeto *vetor;
    int quantidade;
    int cachetam;
} heap;

typedef heap *ponteiro;

ponteiro criar_heap(int cachetam){ //funcao para criar o heap inicial
    ponteiro cache = malloc(sizeof(heap));
    cache->vetor = malloc(cachetam*(sizeof(objeto)));
    cache->quantidade = 0;
    cache->cachetam = cachetam;
    return cache;
}

void calcular_prioridade(objeto *comprioridade, int sequencia[], int seqtam, int auxiliar[]){ //calcula a partir da posicao no vetor da prox apariçao do mesmo número
    for(int i=seqtam; i>=0; i--){
        if(auxiliar[sequencia[i]]==-1){
            comprioridade[i].numero = sequencia[i];
            comprioridade[i].prioridade = INT_MAX;
            auxiliar[sequencia[i]] = i;

        }
        else{
            comprioridade[i].numero = sequencia[i];
            comprioridade[i].prioridade = auxiliar[sequencia[i]];
            auxiliar[sequencia[i]] = i;
        }
    }
}

int existe(ponteiro cache, int numero){ //verifica se o objeto já existe no cache
    for(int i=0; i<cache->quantidade; i++){
        if(cache->vetor[i].numero == numero){
            return 1;
        }
    }
    return 0;

}

#define PAI(i) ((i-1)/2)
void subir(ponteiro cache, int k){ //reorganiza após cada insercao
    if(k>0 && cache->vetor[PAI(k)].prioridade<cache->vetor[k].prioridade){
        objeto atual = cache->vetor[k];
        cache->vetor[k] = cache->vetor[PAI(k)];
        cache->vetor[PAI(k)] = atual;

        subir(cache, PAI(k));

    }
}

void inserir(objeto comprioridade, ponteiro cache){
    cache->vetor[cache->quantidade]= comprioridade;
    cache->quantidade++;
    subir(cache, cache->quantidade-1);
}

#define esquerdo(i) (2*i + 1)
#define direito(i) (2*i + 2)
void descer(ponteiro cache, int k){ //reorganiza após cada remoçao
    int maior;
    if(esquerdo(k)<cache->quantidade){
        maior = esquerdo(k);
        if(direito(k)<cache->quantidade && cache->vetor[esquerdo(k)].prioridade<cache->vetor[direito(k)].prioridade){
            maior = direito(k);
        }
        if(cache->vetor[k].prioridade<cache->vetor[maior].prioridade){
            objeto atual = cache->vetor[k];
            cache->vetor[k] = cache->vetor[maior];
            cache->vetor[maior]= atual;

            descer(cache, maior);

        }
    }
}

void remover(ponteiro cache){
    cache->vetor[0] = cache->vetor[cache->quantidade - 1]; 
    cache->quantidade--;
    descer(cache, 0);
}

void mudar_prioridade(ponteiro cache, objeto comprioridade){
    for(int i=0; i<cache->quantidade; i++){
        if(cache->vetor[i].numero == comprioridade.numero){
            if(cache->vetor[i].prioridade<comprioridade.prioridade){
                cache->vetor[i].prioridade = comprioridade.prioridade;
                subir(cache, i);
            }else{
                cache->vetor[i].prioridade = comprioridade.prioridade;
                descer(cache, i);
            }
        }
    }
}


int main(void){
    int cachetam; //tamanho do cache
    int objetos;
    int seqtam; //tamanho da sequencia
    scanf("%d %d %d", &cachetam, &objetos, &seqtam);

    int *sequencia = malloc(seqtam*sizeof(int)); //aloca todos os objetos que serao usados em um vetor
    for(int i=0; i<seqtam; i++){
        scanf("%d", &sequencia[i]);
    }

    objeto *comprioridade = malloc(seqtam*sizeof(objeto)); //cria um vetor com essas structs

    int *auxiliar = malloc(objetos*sizeof(int)); //aloca um vetor auxiliar para armazenar os objetos que serao usados
    for(int i=0; i<objetos; i++){
        auxiliar[i]=-1;
    }

    calcular_prioridade(comprioridade, sequencia, seqtam, auxiliar);

    ponteiro cache = criar_heap(cachetam);

    int insercoes = 0;

    for(int i= 0; i<seqtam; i++){
        if(existe(cache, comprioridade[i].numero)==0){
            if(cache->quantidade == cache->cachetam){
                remover(cache);
            }
            inserir(comprioridade[i],cache);
            insercoes++;
        }else{
            mudar_prioridade(cache, comprioridade[i]);
        }
    }
    printf("%d\n", insercoes);

    free(sequencia);
    free(comprioridade);
    free(cache->vetor);
    free(cache);

    return 0;
}