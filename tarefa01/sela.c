#include <stdio.h>

// ponto de sela = único mínimo da linha e único máximo da coluna

int verificalinha(int i, int j, int coluna, int matriz[][100]) { // verifica se é o mínimo na coluna
    int pontolinha = 1;
    for (int n=0; n<coluna; n++) { //deixa a linha fixa e varia a posição da coluna
        if (matriz[i][n] < matriz [i][j]) {
            pontolinha = 0; // não é ponto de sela
            return pontolinha;
        }
    }
    return pontolinha;
}

int verificaunicoL (int i, int j, int coluna, int matriz [][100]){
    int unicolinha =1;
    for (int u=0; u<coluna; u++) { //confere se o ponto é único
        if (u != j && matriz[i][u] == matriz[i][j]) {
            unicolinha = 0; //nao é unico
            return unicolinha;
                }
            }
    return unicolinha;
}

int verificacoluna(int i, int j, int linha, int matriz[][100]) { // verifica se é máximo na coluna
    int pontocoluna = 1;
    for (int m=0; m<linha; m++) {
        if (matriz [m][j] > matriz [i][j]){
            pontocoluna = 0;
            return pontocoluna;
        }
    }
    return pontocoluna;
}

int verificaunicoC (int i, int j, int linha, int matriz[][100]){ // verifica se é único na coluna
    int unicoluna = 1;
    for (int v=0; v<linha; v++) {
        if(v!=i && matriz[v][j]== matriz[i][j]) {
        unicoluna =0;
        return unicoluna;
        }
    }
    return unicoluna;
}

int main () {
    int matriz [100][100];
    int linha, coluna;
    scanf("%d %d", &linha, &coluna);

    for (int i=0; i<linha; i++) { //armazena os elementos na matriz
        for (int j=0; j< coluna; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    for (int i=0; i<linha; i++) {
        for (int j=0; j<coluna; j++) { //percorre toda a matriz
            int pontolinha = verificalinha(i, j, coluna, matriz);
            int unicolinha = verificaunicoL(i,j,coluna, matriz);
            int pontocoluna = verificacoluna(i,j,linha,matriz);
            int unicoluna = verificaunicoC(i,j,linha,matriz);

            if (pontolinha==1 && pontocoluna==1 && unicolinha==1 && unicoluna==1) { //compara se o mínimo entre as listas também é o máximo entre as colunas e se sao únicos
                printf("(%d, %d) eh ponto de sela com valor %d", i,j, matriz [i][j]);
                return 0;
            }
        }
    }
    printf("nao existe ponto de sela");
    return 0;
}