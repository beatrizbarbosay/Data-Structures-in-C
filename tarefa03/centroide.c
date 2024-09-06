#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcularmedia(double**matriz, int d, int n, char tipo[]){ //funcao para calcular a media dos pontos de cada coluna da matroiz, ela também possui todos os comandos necessarios para calcular o centroide sem normalizar
    double*centroide=((double*)malloc(d*sizeof(double))); //cria um vetor para armazenar a media calculada
    for(int j=0; j<d; j++){
        centroide[j]=0.0; // inicializa o vetor
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){
            centroide[j]+=matriz[i][j]; //faz a soma dos valores da matriz
        }
    }
    for(int j=0; j<d; j++){
        centroide[j]=centroide[j]/n; //divide pela quantidade de elementos em cada coluna
    }
    printf("%s: ", tipo);  
    for(int j=0; j<d; j++){ //printa as medias calculadas
        printf("%.3f ", centroide[j]); 
    }
    printf("\n");
    free(centroide);
}

void janela(double**pontos, int d, int n){
    double** matriz2=((double**)malloc(n*sizeof(double*))); //matriz para armazenar os valores normalizados
    for(int i=0; i<n; i++){
        matriz2[i]=(double*)malloc(d*sizeof(double));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){
            matriz2[i][j]=0.0;
        }
    }
    for(int j=0; j<d; j++){
        double maximo=pontos[0][j]; //coloca o primeiro elemento da coluna como maximo e minimo para o comparar com o resto
        double minimo=pontos[0][j];
        for(int i=1; i<n; i++){
            if(pontos[i][j]>maximo){
                maximo=pontos[i][j]; //encontra o maximo de cada coluna
            }
            if(pontos[i][j]<minimo){
                minimo=pontos[i][j]; //encontra o minimo de cada coluna
            }
        }
        for (int i=0; i<n; i++){
            if(maximo!=minimo){ //normaliza cada valor da matriz com base nos maximos e minimos de cada coluna
                matriz2[i][j]=((2*(pontos[i][j]-minimo)/(maximo-minimo))-1);
            }else {
                matriz2[i][j]=0;
            }
        }
    }    
    calcularmedia(matriz2, d, n, "janela");

    for (int i = 0; i < n; i++) {
        free(matriz2[i]); 
    }
    free(matriz2); 
}

void normal(double**pontos, int d, int n){
    double*norma=(double*)malloc(n*sizeof(double)); //vetor que vai armazenar as normas de cada coluna
    for(int j=0; j<n; j++){
        norma[j]=0.0;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){
            norma[i]+=(pontos[i][j]*pontos[i][j]);
        }
        norma[i]= sqrt(norma[i]);//calcula a norma
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){
            pontos[i][j]= ((pontos[i][j])/norma[i]);//divide cada elemento da linha pela norma referente
        }
    }
    calcularmedia(pontos,d,n,"normal");
    free(norma);
}

int main(void){
    int d=0;
    int n=0;
    scanf("%d %d", &d, &n);
    double**pontos=(double**)malloc(n*sizeof(double*)); //cria uma ponteiro que aponta para uma array de ponteiros contendo uma array de doubles com tamanho n*double*
    for(int i=0; i<n; i++){
        pontos[i]=(double*)malloc(d*sizeof(double)); //cria uma matriz alocada na memória
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){
            scanf("%lf", &pontos[i][j]); //recebe os scanfs aloca valores para a matriz
        }
    }
    calcularmedia(pontos, d, n, "nenhum");
    janela(pontos, d, n);
    normal(pontos, d, n);

    for (int i = 0; i < n; i++) {
        free(pontos[i]); 
    }
    free(pontos); 
    return 0;
}