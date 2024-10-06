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

void printar(ponteiro expressao){
    if(expressao !=NULL){
        if((expressao->esquerdo!=NULL || expressao->direito!=NULL)&& expressao->valor!= '!'){
            printf("(");
        }
        printar(expressao->esquerdo);
        printf("%c", expressao->valor);
        printar(expressao->direito);
        if((expressao->esquerdo!=NULL || expressao->direito!=NULL)&& expressao->valor !='!'){
            printf(")");
        }
    }
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
        ponteiro direito= criararvore();
        no->direito = direito;
        scanf(" %c", &c);
        return no; 
    }else if(c=='!'){
        ponteiro direito = criararvore();
        ponteiro no = criarno('!');
        no->direito = direito;
        return no;
    }else{
        return criarno(c);
    }
}

void demorgan(ponteiro* expressao){
    if(*expressao==NULL){
        return;
    }
    demorgan(&((*expressao)->esquerdo));
    demorgan(&((*expressao)->direito));

    ponteiro atual= *expressao; 
    ponteiro anterior = NULL;
    while(atual!=NULL && atual->valor != '!'){ //percorre a arvore ate achar um comando "!"
        anterior = atual;
        atual= atual->direito;
    }
    if(atual!= NULL && atual->direito!=NULL && atual->direito->valor == '!'){//condicao para dupla negacao
        ponteiro morgan= atual->direito;
        ponteiro valor = morgan->direito;
        if(anterior!= NULL){
            anterior->direito = valor; 
        }else{
            *expressao=valor;
        }
        free(atual);
        free(morgan);
    }
}


int main(void){
    arvore *arvbin= malloc(sizeof(arvore)); 
    arvbin->expressao=criararvore(); //cria arvore inicial

    printar(arvbin->expressao);
    printf("\n");
    demorgan(&(arvbin-> expressao));
    printar(arvbin->expressao);


    return 0;

}