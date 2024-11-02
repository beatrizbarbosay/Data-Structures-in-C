#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> // Include this header for malloc
#define MAX 1783

typedef struct no { // Define the 'no' type
    char chave[26];
    struct no *prox;
} no;

typedef no *ponteiro;

typedef struct { //estrutura do hash
    ponteiro vetor[MAX];
} hash;

typedef hash *phash;

int calcular_hash(char *chave){ //calcula o numero associado
    int i, n =0;
    for(i=0; i<strlen(chave); i++){
        n=(256*n + chave[i]) % MAX;
    }
    return n;
}

ponteiro inserir_lista(ponteiro p, char *chave){
    ponteiro novo = (ponteiro)malloc(sizeof(no));
    strcpy(novo->chave, chave);
    novo->prox = p;
    return novo;
}

void inserir_hash(phash t, char *chave){
    int n = calcular_hash(chave);
    t->vetor[n] = inserir_lista(t->vetor[n], chave);
}

int buscar_hash(phash t, char *chave){
    int n = calcular_hash(chave);
    if (t->vetor[n] == NULL){
        return 0;
    }else{
        ponteiro p = t->vetor[n];
        while(p != NULL){
            if(strcmp(p->chave, chave) == 0){
                return 1;
            }
            p = p->prox;
        }
        return 0;
    }
}

int main(void){
    int m, n;
    scanf("%d %d", &m, &n);
    phash tabela = (phash)malloc(sizeof(hash));
    for(int i=0; i<m; i++){
        char chave[26];
        scanf("%s", chave);
        inserir_hash(tabela, chave);
    }
    for(int i =0; i<n; i++){
        char palavra[26];
        scanf("%s", palavra);
        if(buscar_hash(tabela, palavra)){
            printf("%s: verde\n", palavra);
        }
    }
    


}