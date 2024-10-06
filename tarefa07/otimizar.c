#include <stdio.h>
#include <stdlib.h>
typedef struct no* ponteiro; 
struct no {
    char valor;
    ponteiro direito;
    ponteiro esquerdo;
};


typedef struct arvore{
    ponteiro expressao;
} arvore;

ponteiro criarno(char valor) {
    ponteiro novo =  malloc(sizeof(struct no));
    novo->valor = valor;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}


ponteiro criararvore(){
    char c;
    scanf(" %c", &c);

    if(c== '('){
        ponteiro esquerdo = criararvore(); //cria a parte esquerda, depois do ( e antes do operador
        char operador;
        scanf(" %c", &operador);
        ponteiro no = criarno(operador); //cria um nó para o operador
        no->esquerdo = esquerdo; //atribui as variaveis da parte esquerda
        ponteiro direito = NULL;

        while(1){
            scanf(" %c", &c);
            if(c==')'){ //quando terminar a subexpressao
                break;
            }else{
                direito = criararvore(); //cria a parte direita, depois do operador
                no->direito = direito; //atribui a parte esquerda
            }
        }
        return no; //retorna a subexpressao       
    }else if(c=='!'){
        ponteiro direito = criararvore();
        ponteiro no = criarno('!');
        no->direito = direito;
        return no;
    }else{
        return criarno(c);
    }
}



int main(void){
    arvore *arvbin= malloc(sizeof(arvore)); 
    arvbin->expressao=criaravore(); //cria arvore inicial




    return 0;

}