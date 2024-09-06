#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 401

int palindromo(char palavra[], int inicio, int fim, int quase,int quase2){
    if(fim<0){ //roda a funcao recursiva até a string acabar
        return (quase2<=quase); //se o numero de caracteres diferentes for menor ou igual ao valor k de en
    }
    if(palavra[inicio]!=palavra[fim]) {
        (quase2)++; //soma valores para a variável toda vez que encontra um caracter diferente
    }
    return palindromo(palavra, inicio+1, fim-1, quase, quase2); //retorna a funcao para que ela acesse a palavra inteira
}

int main(void){
    int quase=0;
    char palavra[MAX];
    scanf("%d",&quase);
    scanf("%400s", palavra);
    int tamanho = strlen(palavra);
    int quase2=0; //variavel auxiliar para armazenar a quantidade de caracteres diferentes
    if(palindromo(palavra, 0, tamanho-1, quase, quase2)){
        printf("sim");
    }else {
        printf("nao");
    }

    return 0;
}




