#include <stdio.h>
#include <stdlib.h>
typedef struct no* ponteiro; //abreviacao
struct no { //cada parte da equacao sera um nó da arvore binaria
    char valor;
    ponteiro direito;
    ponteiro esquerdo;
};

typedef struct arvore{
    ponteiro expressao;
} arvore;

ponteiro criarno(char valor) { //funcao para adicionar novos elementos a equacao
    ponteiro novo =  malloc(sizeof(struct no));
    novo->valor = valor;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

void printar(ponteiro expressao){ //printa a expressao (inordem)
    if(expressao !=NULL){
        if((expressao->esquerdo!=NULL || expressao->direito!=NULL)&& expressao->valor!= '!'){
            printf("("); //printa a abertura de subexpressoes
        }
        printar(expressao->esquerdo);
        printf("%c", expressao->valor);
        printar(expressao->direito);
        if((expressao->esquerdo!=NULL || expressao->direito!=NULL)&& expressao->valor !='!'){
            printf(")"); //printa o fechamento de subexpressoes
        }
    }
}

ponteiro criararvore(){ //cria a arvore binaria a partir dos scanfs
    char c;
    scanf(" %c", &c);

    if(c== '('){ //cria uma nova subexpressao
        ponteiro esquerdo = criararvore(); //cria a parte esquerda, depois do ( e antes do operador
        char operador;
        scanf(" %c", &operador);
        ponteiro no = criarno(operador); //cria um nó para o operador
        no->esquerdo = esquerdo; //atribui as variaveis da parte esquerda
        ponteiro direito= criararvore(); //cria a parte direita
        no->direito = direito;
        scanf(" %c", &c);
        return no; 
    }else if(c=='!'){ //cria apenas parte direita
        ponteiro direito = criararvore(); 
        ponteiro no = criarno('!');
        no->direito = direito;
        return no;
    }else{
        return criarno(c); //adiciona a, b, etc
    }
}

void demorgan(ponteiro* expressao){ //funcao para manipular a arvore binaria a partir das regras de deMorgan
    if(*expressao==NULL){
        return;
    }
    demorgan(&((*expressao)->esquerdo)); //forma recursiva para fazer os 2 lados da arvore
    demorgan(&((*expressao)->direito));

    ponteiro atual= *expressao; 
    ponteiro anterior = NULL;
    while(atual!=NULL && atual->valor != '!'){ //percorre a arvore ate achar um comando "!" e marca o nó anterior
        anterior = atual;
        atual= atual->direito;
    }
    if(atual!= NULL && atual->direito!=NULL && atual->direito->valor == '!'){//condicao para dupla negacao
        ponteiro morgan= atual->direito;
        ponteiro valor = morgan->direito;
        if(anterior!= NULL){
            anterior->direito = valor; //exlui a dupla negacao
        }else{
            *expressao=valor;
        }
    }else if(atual!=NULL && atual->direito!=NULL &&(atual->direito->valor=='&' || atual->direito->valor =='|')){ //condicao para prox regra
        ponteiro morgan = atual->direito;
        if(anterior!=NULL){
            anterior-> direito = morgan;
        }else{
            *expressao = morgan;
        }
        if(morgan->valor == '|'){ //muda & para | e vice versa
            morgan->valor = '&';
        }else{
            morgan->valor = '|';
        }

        ponteiro antigoesq = morgan->esquerdo;
        ponteiro antigodir = morgan->direito;
        ponteiro novoesq = criarno('!'); //faz a "distributiva"da negacao
        ponteiro novodir = criarno('!');
        morgan->esquerdo = novoesq;
        morgan->direito = novodir;
        novoesq->direito = antigoesq; //reconecta os antigos valores
        novodir->direito = antigodir;
        
    }else{ //garante que a funcao seja recursiva ate nao haver mais nada para simplificar por deMorgan
        return;
    }
    demorgan(expressao);
}

int equivalencia(ponteiro no1, ponteiro no2){ //testar equivalencia, compara nó por nó, se direito e esquerdo sao iguais
    if(no1 == NULL && no2==NULL){
        return 1;
    }else if(no1==NULL && no2!=NULL){
        return 0;
    }else if(no1->valor != no2->valor){
        return 0;
    } //teste para todas as condicoes, inclusive as condicoes de (c|d)|(d|c) ...
    return (equivalencia(no1->esquerdo, no2-> esquerdo) && equivalencia(no1->direito, no2->direito))||(equivalencia(no1->esquerdo, no2->direito)&&equivalencia(no1->direito, no2->esquerdo));    
}


void simplificar(ponteiro* expressao){ //faz as regras de simplificaçao 
    if(*expressao==NULL){
        return;
    }
    simplificar(&((*expressao)->esquerdo)); 
    simplificar(&((*expressao)->direito));

    ponteiro atual= *expressao; 
    while(atual != NULL && atual->direito != NULL && atual->direito->valor != 'T'){ //simplificacoes para T
        atual= atual->direito;
    }
    if( atual!=NULL && atual->direito!=NULL && atual->valor== '|'){ //caso o que venha antes seja |
        atual->valor= 'T'; //simplifica para T
        atual->direito = NULL;
        atual->esquerdo = NULL;
    }else if(atual != NULL && atual->valor == '&' && atual->direito != NULL){ //caso seja &
        ponteiro exp = atual->esquerdo; //simplifica para expressao ao lado de T
        if(exp!=NULL){
        atual->valor = exp->valor;
        atual->direito = exp->direito;
        atual->esquerdo = exp->esquerdo;
        }
    }else if(atual != NULL && atual->valor == '!' && atual->direito != NULL){ //caso o que venha antes seja negacao
        atual->valor= 'F'; //muda para F
        atual->direito = NULL;
        atual->esquerdo = NULL;
    }
    atual= *expressao; //faz a mesma coisa mas para o caso de T estar do lado esquerdo da expressao
    while(atual != NULL && atual->esquerdo != NULL && atual->esquerdo->valor != 'T'){ 
        atual= atual->esquerdo;
    }
    if(atual != NULL && atual->valor == '|' && atual->esquerdo != NULL){
        atual->valor= 'T';
        atual->direito = NULL;
        atual->esquerdo = NULL;
    }else if(atual != NULL && atual->valor == '&' && atual->esquerdo != NULL){
        ponteiro exp = atual->direito;
        if(exp!=NULL){
        atual->valor = exp->valor;
        atual->direito = exp->direito;
        atual->esquerdo = exp->esquerdo;
        }
    }


    atual= *expressao; //testa as mesmas condicoes para F, aplicando seus resultados equivalentes a cada condicao
    while(atual != NULL && atual->direito != NULL && atual->direito->valor != 'F'){ 
        atual= atual->direito;
    }
    if( atual!=NULL && atual->direito!=NULL && atual->valor== '|'){
        ponteiro exp = atual->esquerdo;
        if(exp!=NULL){
            atual->valor = exp->valor;
            atual->direito = exp->direito;
            atual->esquerdo = exp->esquerdo;
        }
    }else if(atual != NULL && atual->valor == '&' && atual->direito != NULL){
        atual->valor= 'F';
        atual->direito = NULL;
        atual->esquerdo = NULL;

    }else if(atual != NULL && atual->valor == '!' && atual->direito != NULL){
        atual->valor= 'T';
        atual->direito = NULL;
        atual->esquerdo = NULL;
    }
    atual= *expressao; 
    while(atual != NULL && atual->esquerdo != NULL && atual->esquerdo->valor != 'F'){ //F no lado esquerdo
        atual= atual->esquerdo;
    }
    if( atual!=NULL && atual->esquerdo!=NULL && atual->valor== '|'){
        ponteiro exp = atual->direito;
        if(exp!=NULL){
            atual->valor = exp->valor;
            atual->direito = exp->direito;
            atual->esquerdo = exp->esquerdo;
        }
    }else if(atual != NULL && atual->valor == '&' && atual->esquerdo != NULL){
        atual->valor= 'F';
        atual->direito = NULL;
        atual->esquerdo = NULL;
    }

    atual = *expressao;
    if(atual->esquerdo!=NULL && atual->direito!=NULL &&(atual->valor == '|' || atual->valor == '&')){ //testa as equivalencias
        if(equivalencia(atual->esquerdo, atual-> direito)){
            *expressao = atual->esquerdo; //deixa apenas com a expressao do lado esquerdo
        }
    }
}

void liberar(ponteiro expressao) { //funcao recursiva para liberar todos os nos da arvore
    if (expressao == NULL) {
        return;
    }
    liberar(expressao->esquerdo);
    liberar(expressao->direito);
    free(expressao);
}


int main(void){
    arvore *arvbin= malloc(sizeof(arvore)); 
    arvbin->expressao=criararvore(); //cria arvore inicial

    printar(arvbin->expressao);
    printf("\n");
    demorgan(&(arvbin-> expressao));
    printar(arvbin->expressao);
    printf("\n");
    simplificar(&(arvbin->expressao));
    printar(arvbin->expressao);

    liberar(arvbin->expressao);
    free(arvbin);

    return 0;
}