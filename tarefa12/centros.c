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

int** dijkstra(ponteirografo g, int origem) {
    int vertices = g->vertices;
    int** distancias = malloc(vertices * sizeof(int*)); //matriz das distancias minimas de uma cidade para todas as outras
    for (int i = 0; i < vertices; i++) {
        distancias[i] = malloc(vertices * sizeof(int));
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            distancias[i][j] = INT_MAX; //inicializa com infinito
        }
    }
    distancias[origem][origem] = 0; //de um vertice pra ele mesmo

    int* visitados = malloc(vertices * sizeof(int)); //para controlar os vertices ja visitados
    for (int i = 0; i < vertices; i++) {
        visitados[i] = 0;
    }

    for (int i = 0; i< vertices - 1; i++) { //encontra o menor caminho para cada vértice
        int mindistancia = INT_MAX;
        int minvertice;
        for (int v = 0; v < vertices; v++) {
            if (visitados[v] == 0 && distancias[origem][v] <= mindistancia) { // menor distancia ainda nao visitada
                mindistancia = distancias[origem][v];
                minvertice = v;
            }
        }
        visitados[minvertice] = 1;
        for (int v = 0; v < vertices; v++) {
            if (visitados[v] == 0 && g->adj[minvertice][v] && distancias[origem][minvertice] != INT_MAX && (distancias[origem][minvertice] + g->adj[minvertice][v] < distancias[origem][v])) { //se a distancia do vertice minvertice para v for menor que a distancia atual
                distancias[origem][v] = distancias[origem][minvertice] + g->adj[minvertice][v]; //atualiza as distancias
            }
        }
    }

    free(visitados);
    return distancias;
}

void encontrar_centros(int vertices, int **distancias, struct cidade listacity[]) {
    int centro1 = -1;
    int centro2 = -1;
    int minimo = INT_MAX; //maior distancia na matriz, pra cada cidade
    int populacao = 0;

    for (int i = 0; i < vertices; i++) { //passa pelos pares de cidade
        for (int j = i + 1; j < vertices; j++) {
            int maiordistancia = 0; //maior distancia de atendimento

            for (int k = 0; k < vertices; k++) { //maior distancia de atendimento para o par
                int distanciacentro; //menor distancia da cidade k para os possíveis centros
                if(distancias[k][i]<distancias[k][j]){
                    distanciacentro = distancias[k][i];   
                }else{
                    distanciacentro = distancias[k][j];
                }
                if (distanciacentro > maiordistancia) {
                    maiordistancia = distanciacentro;
                }
            }

            int soma = listacity[i].populacao + listacity[j].populacao; //soma da populacao
            if (maiordistancia < minimo || (maiordistancia == minimo && soma > populacao)) { //define os pares com base nas distancias de atendimento e somas
                minimo = maiordistancia;
                populacao = soma;
                centro1 = i;
                centro2 = j;
            }
        }
    }

    printf("Centros de distribuicao: %s e %s\n", listacity[centro1].nome, listacity[centro2].nome);
    printf("Distancia de atendimento: %d\n", minimo);
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
    int **distancias= malloc(vertices*sizeof(int*));
    for(int i=0; i<vertices; i++){
        distancias[i] = dijkstra(mapa, i)[i];        
    }
    encontrar_centros(vertices, distancias, listacity);
    for (int i = 0; i < vertices; i++) {
        free(distancias[i]);
    }

    free(distancias);
    destroi_grafo(mapa);
    return 0;
}
