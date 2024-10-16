#include "funcoes.h"

int main(void){
    lista *cobrainteira= malloc(sizeof(lista)); //inicializa a lista ligada que representará a cobra
    cobrainteira->cabeca=NULL;

    int linham=0;
    int colunam=0;
    char inicial[MAX];
    scanf("%s %d %d", inicial, &linham, &colunam);//aloca e inicializa a matriz
    char**matriz=(char**)malloc(linham*sizeof(char*));
    for(int i=0; i<linham; i++){
        matriz[i]=(char*)malloc(colunam*sizeof(char));
    }
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            matriz[i][j]='_';
        }
    }

    int linhacobra=0; //coloca a cobra no lugar inicial
    int colunacobra=0;
    scanf("%s %d %d", inicial, &linhacobra, &colunacobra);
    adicionarpedaco(cobrainteira, matriz, linhacobra, colunacobra);

    int linhafruta=0;
    int colunafruta=0;

    while(1){ //vai recebendo os comandos
        char comando[MAX];
        scanf("%s", comando);
        if(strcmp(comando,"FRUTA")==0){ //coloca fruta na matriz e printa
            scanf("%d %d",&linhafruta, &colunafruta);
            matriz[linhafruta][colunafruta]='*';
            printarmatriz(matriz, linham, colunam);
            continue;
        }
        //realiza cada movimento, guardando as coordenadas da cabeca antiga e vendo, um por um, as condicoes de borda
        if(strcmp(comando,"w")==0){ 
            linhacobra = cobrainteira->cabeca->posicaolinha; 
            colunacobra = cobrainteira->cabeca->posicaocoluna;
            cobrainteira->cabeca->posicaolinha-= 1;
            limitelinha(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"s")==0){
            linhacobra = cobrainteira->cabeca->posicaolinha;
            colunacobra = cobrainteira->cabeca->posicaocoluna;
            cobrainteira->cabeca->posicaolinha +=1;
            limitelinha(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"a")==0){
            linhacobra = cobrainteira->cabeca->posicaolinha;
            colunacobra = cobrainteira->cabeca->posicaocoluna;
            cobrainteira->cabeca->posicaocoluna -=1;
            limitecoluna(cobrainteira, linham, colunam);
        }else if(strcmp(comando,"d")==0){
            linhacobra = cobrainteira->cabeca->posicaolinha;
            colunacobra = cobrainteira->cabeca->posicaocoluna;
            cobrainteira->cabeca->posicaocoluna+=1;
            limitecoluna(cobrainteira, linham, colunam);
        }
        if(youlose(cobrainteira)){ //verifica se bateu
            printf("GAME OVER");
            break;
        }

        if(cobrainteira->cabeca->posicaocoluna==colunafruta && cobrainteira->cabeca->posicaolinha==linhafruta){ //se a cobra comer a fruta
            comeufruta(cobrainteira, matriz, linhacobra, colunacobra);
        }
        movercobra(cobrainteira, linhacobra, colunacobra);

        //atualiza a matriz e a printa após cada comando
        atualizarmatriz(matriz,linham, colunam, cobrainteira);
        printarmatriz(matriz,linham,colunam);

        if(youwin(matriz,linham,colunam)){ //verifica se ganhou
            printf("YOU WIN");
            break;
        }
    }
    freecobra(cobrainteira);
    freematriz(matriz, linham, colunam);
    free(cobrainteira);
    return 0;
}