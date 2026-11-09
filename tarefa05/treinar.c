#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct no *p_no; // Ponteiro para a estrutura
struct no { // Estrutura que representa cada nó da lista ligada
    char nucleo; // Caractere que armazena a núcleo-base
    p_no prox;   // Ponteiro para o próximo nó
};

typedef struct lista { // Lista ligada dos núcleos
    p_no inicio; // Ponteiro para o início da lista
} lista;

// Função para inserir um novo nó na lista
void inserir(lista *sequencia, char caractere, int posicao) { 
    p_no novo = malloc(sizeof(struct no)); // Cria um novo nó
    novo->nucleo = caractere; // Atribui o caractere
    novo->prox = NULL; // Inicializa o próximo nó como NULL

    if (posicao != 0) { // Se a posição não é 0
        p_no atual = sequencia->inicio; // Cria um ponteiro auxiliar 
        for (int i = 0; i < posicao - 1 && atual != NULL; i++) { // Percorre até encontrar a posição
            atual = atual->prox; // Move para o próximo nó
        }
        if (atual != NULL) { // Se a posição é válida
            novo->prox = atual->prox; // O novo nó aponta para o próximo nó de 'atual'
            atual->prox = novo; // O nó anterior aponta para o novo nó
        } else {
            // Se a posição é maior que o tamanho da lista, adicione ao final
            free(novo); // Liberar memória se a inserção não for possível
            printf("Posição inválida para inserção.\n");
            return;
        }
    } else { // Se a posição for 0, o novo será o primeiro
        novo->prox = sequencia->inicio; // O novo nó aponta para o antigo início
        sequencia->inicio = novo; // Atualiza o início da lista para o novo nó
    }
    printf("%c inserido em %d\n", novo->nucleo, posicao); // Mensagem de confirmação
}

int main(void) {
    lista *sequencia = malloc(sizeof(lista)); // Aloca memória para a lista
    sequencia->inicio = NULL; // Inicializa a lista como vazia
    char comando[MAX]; // Buffer para armazenar comandos

    // Loop que continua até que o comando "sair" seja recebido
    while (1) { // Loop infinito para permitir a inserção contínua
        printf("Digite um comando (ou 'sair' para encerrar): ");
        scanf("%s", comando); // Lê o comando

        // Se o comando for "sair", sai do loop
        if (strcmp(comando, "sair") == 0) {
            break;
        }

        char operacao[MAX]; // Buffer para armazenar a operação
        // Se o comando não for "sair", lê a operação
        if (strcmp(comando, "inserir") == 0) {
            char caractere; // Variável para armazenar o caractere
            int posicao;    // Variável para armazenar a posição de inserção
            scanf(" %c %d", &caractere, &posicao); // Lê o caractere e a posição
            inserir(sequencia, caractere, posicao); // Chama a função de inserção
        } 
        // Você pode adicionar outros comandos aqui como "remover", "imprimir", etc.
    }

    // Libera a memória alocada para a lista antes de encerrar o programa
    free(sequencia); 
    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}