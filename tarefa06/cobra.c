#include <stdio.h>
#include <string.h>
#define MAX 50

typedef struct cobra *ponteiro; 
struct cobra { //nós de cada pedaço da cobra
    int posicaolinha;
    int posicaocoluna;
    ponteiro prox;
    ponteiro anterior;
};

typedef struct lista{ //cabeça da cobra
    ponteiro cabeca;
} lista;

void printarmatriz(int matriz[],int linham, int colunam){
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            printf("%c", matriz[i][j]);
        }
    }
}
void movercobra(lista*cobrainteira, int linham, int colunam){
    ponteiro atual = cobrainteira->cabeca;
    int atualinha=0;
    int atualcoluna=0;
    int antigalinha=atual->posicaolinha;
    int antigacoluna=atual->posicaocoluna;\
     
    if(atual->posicaolinha == linham){ //define as condicoes de borda
        atual->posicaolinha= 0;
    }
    if(atual->posicaolinha == 0){
        atual->posicaolinha= linham;
    }
    if(atual->posicaocoluna == colunam){
        atual->posicaolinha= 0;
    }
    if(atual->posicaocoluna == 0){
        atual->posicaolinha= colunam;
    }
    atual=atual->prox;

    while(atual!=NULL){ //move todo o corpo de forma que cada nó siga a posicao do nó anterior
        atualinha= atual->posicaolinha;
        atualcoluna= atual->posicaocoluna;
        atual->posicaolinha = antigalinha;
        atual->posicaocoluna = antigacoluna;
        antigalinha=atualinha;
        antigacoluna=atualcoluna;
        atual=atual->prox;
    }
}

void atualizarmatriz(int **matriz){
    
}

Bool youwin(int **matriz[], int linham, int colunam){ //verifica se a cobra ocupa toda a matriz
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            if(matriz[i][j]!='#'){
                return 0;
            }else{
                return 1;
            }
        }
    }
}

int main(void){
    lista *cobrainteira= malloc(sizeof(lista)); //inicializa a lista ligada que representará a cobra
    cobrainteira->cabeca=NULL;

    int linham=0;
    int colunam=0;
    char matriz[MAX];
    scanf("%s %d %d", matriz, &linham, &colunam);//aloca e inicializa a matriz
    char**matriz=(char**)malloc(linham*sizeof(char*));
    for(int i=0; i<linham; i++){
        matriz[i]=(char*)malloc(colunam*sizeof(char));
    }
    for(int i=0; i<linham; i++){
        for(int j=0; j<colunam; j++){
            matriz[i][j]='_ ';
        }
    }

    int linhacobra=0; //coloca a cobra no lugar inicial
    int colunacobra=0;
    char cobra[MAX];
    scanf("%s %d %d", cobra, &linhacobra, &colunacobra);
    cobrainteira->cabeca->posicaolinha=linhacobra;
    cobrainteira->cabeca->posicaocoluna=colunacobra;
    matriz[linhacobra][colunacobra]='# ';

    while(1){
        char comando[MAX];
        scanf("%s", comando);
        if(strcmp(comando,"FRUTA")==0){
            int linhafruta=0;
            int colunafruta=0;
            scanf("%d %d",&linhafruta, &colunafruta);
            matriz[linhafruta][colunafruta]='* ';
            printarmatriz(matriz, linham, colunam);
        }else if(strcmp(comando,"w")==0){
            cobrainteira->cabeca->posicaocoluna=(colunacobra-1);
            movercobra(cobrainteira);
        }else if(strcmp(comando,"s")==0){
            cobrainteira->cabeca->posicaocoluna=(colunacobra+1);
            movercobra(cobrainteira);
        }else if(strcmp(comando,"a")==0){
            cobrainteira->cabeca->posicaolinha=(linhacobra-1);
            movercobra(cobrainteira);
        }else if(strcmp(comando,"d")==0){
            cobrainteira->cabeca->posicaolinha=(linhacobra-1);
            movercobra(cobrainteira);
        }
        if(cobrainteira->cabeca->posicaocoluna==colunafruta && cobrainteira->cabeca->posicaolinha==linhafruta){
            matriz[linhafruta][colunafruta]=='# ';
        }
        printmatriz()
        int linharabo, colunarabo=rabocobra(matriz, cobrainteira);
        if(matriz[cobrainteira->cabeca->posicaolinha][cobrainteira->cabeca->posicaocoluna]=='_ '){
            printf("YOU LOSE");
            return 0;
        }
        if(youwin(matriz,linham,colunam)){
            printf("YOU WIN");
        }
    
    }
    return 0;
    
}   