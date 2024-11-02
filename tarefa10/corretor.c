#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 1783

typedef struct no { 
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

int caractere_mais(phash t, char *palavra){
    int tam = strlen(palavra);
    char novapalavra[26];
        for(int i=0; i<tam; i++){ //percorre a palavra original
        int k=0; 
        for(int j=0; j<tam; j++){ //cria uma nova palavra sem o caractere i
            if(j!=i){ 
                novapalavra[k++] = palavra[j];
            }
        }
        novapalavra[k] = '\0';
        if(buscar_hash(t, novapalavra)==1){ //busca os hash da nova palavra
            return 1;
        }
    }
    return 0;
}

int caractere_menos(phash t, char *palavra){
    int tam = strlen(palavra);
    char novapalavra[27];
    char alfabeto[27]="abcdefghijklmnopqrstuvwxyz";
    for(int i=0; i<tam; i++){ //percorre a palavra original
        for(int j=0; j<26; j++){
            int k=0;
            for(int l=0; l<tam; l++){ //cria uma nova palavra com um caractere a mais
                if(l==i){ //se a posição for igual a i, insere o caractere do alfabeto
                    novapalavra[k++] = alfabeto[j];
                }else{ //se não, insere o caractere da palavra original
                    novapalavra[k++] = palavra[l];
                }
            }
            novapalavra[k] = '\0';
            if(buscar_hash(t, novapalavra)==1){
                return 1;
            }
        }
    }
    return 0;
}

int caractere_trocado(phash t, char *palavra){
    int tam = strlen(palavra);
    char novapalavra[26];
    char alfabeto[27]="abcdefghijklmnopqrstuvwxyz";
    for(int i=0; i<tam; i++){ 
        strcpy(novapalavra, palavra);
        for(int j=0; j<26; j++){
            if(palavra[i] != alfabeto[j]){
                novapalavra[i] = alfabeto[j];
                if(buscar_hash(t, novapalavra)==1){
                    return 1;
                }
            }
        }
    }
    return 0;

}

int amarelo(phash t, char *palavra) {
    return caractere_mais(t, palavra) || caractere_menos(t, palavra) || caractere_trocado(t, palavra);
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
        }else{
            if(amarelo(tabela, palavra)){
                printf("%s: amarelo\n", palavra);
            }else{
                printf("%s: vermelho\n", palavra);
            }
        }
    }
}