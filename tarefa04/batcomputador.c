#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define LIXO 0

int duplicar_memoria(int**batmemoria, int memoriatotal){ //aumentar a memória quando necessário
    int novotamanho = (memoriatotal)*2; //pega o valor da memoria total antiga e duplica
    int *novamemoria= malloc(novotamanho*sizeof(int)); //define um novo ponteiro para a memoria com o tamanho atualizado
    for(int i=0; i<novotamanho; i++){ //inicializa novo vetor
        novamemoria[i]=LIXO;
    }
    for(int i=0; i<memoriatotal; i++){ //coloca os elementos da memoria antiga na nova memoria
        novamemoria[i]=(*batmemoria)[i]; 
    }
    free(*batmemoria); //libera a memoria antiga
    *batmemoria = novamemoria;//define o novo vetor da batmemoria
    return novotamanho;
}

void batalloc(int **batmemoria, int *memoriausada, int *memoriatotal, int tamanho){ //alocar novos vetores na batmemoria
    int inicio= -1; 
    for(int i=0; i<*memoriatotal; i++){//verifica qual o primeiro espaco livre da memoria
        if((*batmemoria)[i]==LIXO){//encontra espaco livre
            int livre=0; 
            for(int j=i; j<*memoriatotal && (*batmemoria)[j]==LIXO; j++){ //verifica se o tamanho é o suficiente para alocar o vetor
                livre++;
                if(livre>=tamanho+1){//tem espaco suficiente
                    inicio=i; 
                    break;
                }
            }
            if(inicio!=-1){ //tem espaco na memoria antes do final do ultimo vetor
                break;
            }
        }
    }
    if(inicio==-1){ //se nao encontrar espaço livre suficiente, aloca no final da memória
        *memoriatotal=duplicar_memoria(batmemoria, *memoriatotal);
        inicio=*memoriausada;
    }
    (*batmemoria)[inicio]=tamanho; //define o int tamanho como primeiro elemento do vetor
    for(int i=1; i<=tamanho; i++){ //aloca os elementos na batmemoria
        scanf("%d", &(*batmemoria)[inicio+i]);
    }
    if(inicio==*memoriausada){  //aumenta a memória usada
        *memoriausada+=tamanho+1;
    }

    printf("%d\n", inicio);
}

void batfree(int *batmemoria, int liberar){
    int inicio = 0;
    inicio=batmemoria[liberar]; //a partir de qual espaço da memoria quer começar a liberar
    for(int i=liberar; i<=liberar+inicio; i++){ //libera todo o resto do vetor
        batmemoria[i]= LIXO;
    }
}

void reduzir_memoria(int *memoriatotal, int **batmemoria, int memoriausada){
    while((*memoriatotal>8)){
        int quartomemoria= (*memoriatotal)/4;
        int reduzir=1;
    
        for(int i=quartomemoria; i<*memoriatotal; i++){ //verifica se há espaço livre na memória após o primeiro quarto
            if((*batmemoria)[i] != LIXO){ //caso encontre espaço usado, nao reduz
                reduzir=0;
                break;
            }
        }
        if(reduzir==1){ //condicao para reduzir a memoria pela metade
            int novotamanho =*memoriatotal/2;
            int *novamemoria= malloc(novotamanho*sizeof(int));  //cria um novo vetor com tamanho pela metade
            for(int i=0; i<novotamanho; i++){ //aloca os valores antigos da batmemoria no novo vetor
                novamemoria[i]=(*batmemoria)[i]; 
            }
            free(*batmemoria);
            *batmemoria = novamemoria; //redefine a bat memoria
            *memoriatotal=novotamanho; //redefine o tamanho da memoria usada
        }else{
            break;
        }
    }
}

void batprint(int *batmemoria){
    int endereco=0;
    scanf("%d", &endereco); //qual endereço que quer ser printado
    int printar= batmemoria[endereco]; //encontra na batmemoria
    for(int i=endereco+1; i<endereco+printar+1; i++){ //printa o vetor referente ao endereço
        printf("%d ", batmemoria[i]);
    }
    printf("\n");
}

void batuso(int *batmemoria, int memoriatotal, int memoriausada){
    int memoria_aloc = 0; //ve quanto da memoria ta sendo usada
    for(int i=0; i<memoriatotal; i++){
        if(batmemoria[i]!= LIXO){
            memoria_aloc++; //encontra os elementos nao vazios
        }
    }
    printf("%d de %d\n", memoria_aloc, memoriatotal);
}

int main(void){
    int memoriatotal=8; //define o valor inicial da bat memoria
    int memoriausada=0;
    int *batmemoria = malloc(memoriatotal*sizeof(int)); //cria um vetor inicial com o tamanho da bat memoria
    for(int i=0; i<memoriatotal; i++){ //inicializa o vetor
        batmemoria[i]=LIXO;
    }
    int numero =0;
    scanf("%d", &numero);
    for(int i=0; i<numero; i++){ //passa pela quantidade de todas as operaçoes
        char operacao[MAX];
        scanf("%s", operacao);
        if(strcmp(operacao, "bat-alloc")==0){ 
            int tamanho=0;
            scanf("%d",&tamanho);
            batalloc(&batmemoria, &memoriausada, &memoriatotal, tamanho);
        }    
        if(strcmp(operacao, "bat-free")==0){
            int liberar=0;
            scanf("%d", &liberar);
            batfree(batmemoria, liberar);
            reduzir_memoria(&memoriatotal, &batmemoria, memoriausada);
        }
        if(strcmp(operacao, "bat-print")==0){
            batprint(batmemoria);
        }
        if(strcmp(operacao, "bat-uso")==0){
            batuso(batmemoria, memoriatotal, memoriausada);
        }
    }
    return 0;
}