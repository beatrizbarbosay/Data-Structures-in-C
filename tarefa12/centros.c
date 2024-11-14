#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct cidade{
    char nome[50];
    int populacao;
};

typedef struct{
    int n;
    int **adj;
    int vertices;
}grafo;

typedef grafo *ponteirografo;

ponteirografo criar_grafo(int vertices){ //matriz de adjacencia 
    int i,j;
    ponteirografo g = malloc(sizeof(grafo));
    g->vertices=vertices;
    g->adj = malloc(vertices*sizeof(int *));
    for(i=0; i<vertices; i++){
        g->adj[i] = malloc(vertices*sizeof(int));
    }
    for(i=0; i<vertices; i++){
        for(j=0; j<vertices; j++){
            g->adj[i][j]=0;
        }
    }
    return g;
}

void inserir_cidade(ponteirografo g, int u, int v, int distancia){
    g->adj[u][v] = distancia;
    g->adj[v][u] = distancia;
}

void destroi_grafo(ponteirografo mapa){
    int i;
    for(i=0; i<mapa->vertices; i++){
        free(mapa->adj[i]);
    }
    free(mapa->adj);
    free(mapa);
}

int* dijkstra(ponteirografo g, int origem) { //retorna um vetor com as distancias minima de uma cidade p todas as outras
    int vertices = g->vertices;
    int* distancias = malloc(vertices * sizeof(int*)); //armazena as distancias minimas
    int* visitados = malloc(vertices * sizeof(int*)); //marcar os que ja foram visitados
    for(int i=0; i<vertices; i++){ //inicializa vertices e distancias
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }
    distancias[origem] = 0;
    for(int i=0; i<vertices; i++){
        int distanciaminima = INT_MAX;
        int u = -1;
        for(int j=0; j<vertices; j++){
            if(visitados[j]==0 && distancias[j]<=distanciaminima){//atualiza a distancia minima se encontrar menor
                distanciaminima = distancias[j];
                u = j;
            }
        }
        visitados[u] = 1;
        for(int v=0; v<vertices; v++){ //atualiza as distancias dos vertices adjacentes
            if(!visitados[v]&& g->adj[u][v] != INT_MAX && distancias[u] != INT_MAX && distancias[u]+g->adj[u][v]<distancias[v]){
                distancias[v] = distancias[u] + g->adj[u][v];
            }
        }
    }
    free(visitados);
    return distancias;
}

int main(void){
    int vertices;
    scanf("%d", &vertices);
    ponteirografo mapa = criar_grafo(vertices);
    struct cidade listacity[10000];
    for(int i=0; i<vertices; i++){
        char nome[50];
        int populacao;
        scanf("%s %d", nome, &populacao);
        strcpy(listacity[i].nome, nome);
        listacity[i].populacao = populacao;
    }
    int caminhos;
    scanf("%d", &caminhos);
    for(int i=0; i<caminhos; i++){ //cria as arestas
        char cidade1[50], cidade2[50];
        int distancia;
        scanf("%s %s %d", cidade1, cidade2, &distancia);
        int u, v;
        for(int j=0; j<vertices; j++){
            if(strcmp(cidade1, listacity[j].nome)==0){ 
                u=j;
            }
            if(strcmp(cidade2, listacity[j].nome)==0){
                v=j;
            }
        }
        inserir_cidade(mapa, u, v, distancia);
    }


    destroi_grafo(mapa);
    return 0;
}