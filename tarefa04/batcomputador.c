#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define LIXO 0xAB167891

int duplicar_memoria(int**batmemoria, int memoriatotal){ //aumentar a memória quando necessário
    int novotamanho = (memoriatotal)*2; //pega o valor da memoria totla antiga e duplica
    int *novamemoria= malloc(novotamanho*sizeof(int)); //define um novo ponteiro para a memoria com o tamanho atualizado
    for(int i=0; i<novotamanho; i++){ //inicializa novo vetor
        novamemoria[i]=0;
    }
    for(int i=0; i<memoriatotal; i++){ //coloca os elementos da memoria antiga na nova memoria
        novamemoria[i]=(*batmemoria)[i]; 
    }
    free(*batmemoria); //libera a memoria antiga
    *batmemoria = novamemoria;//define o novo vetor da batmemoria
    return novotamanho;
}

void batalloc(int **batmemoria, int *memoriausada, int *memoriatotal, int tamanho){ //alocar novos vetores na batmemoria
    while(*memoriausada+tamanho+1> *memoriatotal){ //verifica se há espaço suficiente na memoria
        *memoriatotal=duplicar_memoria(batmemoria, *memoriatotal); //aumenta a memoria se nao houver
    } 
    int inicio= *memoriausada; //marca o inicio do código com o proximo valor livre da memoria 
    (*batmemoria)[inicio]=tamanho; //define o primeiro elemento do vetor

    for(int i=1; i<=tamanho; i++){ //aloca os elementos na batmemoria
        scanf("%d", &(*batmemoria)[inicio+i]);
    }
    *memoriausada+=tamanho+1;//aumenta o valor da memoria usada

    printf("%d\n", inicio);
}

void batfree(int *batmemoria, int liberar, int memoriausada){
    int inicio = batmemoria[liberar];
    for(int i=liberar; i<liberar+inicio+1; i++){
        batmemoria[i]= LIXO;    
    }
    for(int i=0; i<memoriausada; i++){
        printf("%d", batmemoria[i]);
    }
}

void reduzir_memoria(){
    
}

int main(void){
    int memoriatotal=8; //define o valor inicial da bat memoria
    int memoriausada=0;
    int *batmemoria = malloc(memoriatotal*sizeof(int)); //cria um vetor inicial com o tamanho da bat memoria
    for(int i=0; i<memoriatotal; i++){ //inicializa o vetor
        batmemoria[i]=0;
    }
    int numero =0;
    scanf("%d", &numero);
    for(int i=0; i<numero; i++){
        char operacao[MAX];
        scanf("%s", operacao);
        if(strcmp(operacao, "bat-alloc")==0){ //operacao para bat-alloc
            int tamanho=0;
            scanf("%d",&tamanho);
            batalloc(&batmemoria, &memoriausada, &memoriatotal, tamanho);
        }    
        if(strcmp(operacao, "bat-free")==0){
            int liberar=0;
            scanf("%d", &liberar);
            batfree(batmemoria, liberar, memoriausada);



            //funcao bat free
        }
        if(strcmp(operacao, "bat-print")==0){
            //funcao bat print
        }
        if(strcmp(operacao, "bat-uso")==0){
          //funcao bat uso
        }
    }


    return 0;
}