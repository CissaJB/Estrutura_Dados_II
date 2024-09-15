#include <stdio.h>
#include <stdlib.h>
//Cecilia de Jesus Barros

// Definição da estrutura da árvore (No)
struct NO {
    int valor;
    struct NO *direita;
    struct NO *esquerda;
};
typedef struct NO* ArvBin;

// Função para inserir um valor na árvore
ArvBin inserir_valor(ArvBin raiz, int num) {
    // Se a árvore estiver vazia, cria o 1° Nó
    if (raiz == NULL) {
        ArvBin novo = (ArvBin)malloc(sizeof(struct NO));
        novo->valor = num;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo; //Retorna a raiz da árvore
    } else {
        // Se a árvore já estiver com dados
        if (num < raiz->valor) //Se o novo nó for menor que a raiz, armazena na esquerda
            raiz->esquerda = inserir_valor(raiz->esquerda, num);
        else //Se o novo nó for menor que a raiz, armazena na direita
            raiz->direita = inserir_valor(raiz->direita, num);
        return raiz;
    }
}

// Função para imprimir a árvore estruturada
void imprimir_arvore(ArvBin raiz, int nivel) {
    if (raiz) {
        imprimir_arvore(raiz->direita, nivel + 1); // Imprime a subárvore direita
        for (int i = 0; i < nivel; i++) 
            printf("  ");
        printf("%d\n", raiz->valor); 
        imprimir_arvore(raiz->esquerda, nivel + 1); // Imprime a subárvore esquerda
    }
}

// Buscando um valor na árvore
ArvBin buscar_valor(ArvBin raiz, int num) {
    // Se a árvore estiver vazia ou o valor for encontrado de primeira (O(1))
    if (raiz == NULL || raiz->valor == num) {
        return raiz;
    }
    // Se o valor for menor que a raiz, procurar na esquerda
    if (num < raiz->valor) {
        return buscar_valor(raiz->esquerda, num);
    // Se o valor for maior que a raiz, procurar na direita
    } else {
        return buscar_valor(raiz->direita, num);
    }
}

// Função para encontrar o valor mínimo na árvore, valor mais a esquerda possível
ArvBin encontrarMinimo(ArvBin raiz) {
    ArvBin atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função para excluir um valor da árvore
ArvBin excluir(ArvBin raiz, int num) {
    //Se a raiz estiver vazia, retorna a raiz = NULL
    if (raiz == NULL) {
        return raiz;
    }
    if (num < raiz->valor) {
        raiz->esquerda = excluir(raiz->esquerda, num);
    } else if (num > raiz->valor) {
        raiz->direita = excluir(raiz->direita, num);
    } else {
        //Nó folha ou com apenas 1 filho
        if (raiz->esquerda == NULL) {
            ArvBin aux = raiz->direita;
            free(raiz);
            return aux;
        } else if (raiz->direita == NULL) {
            ArvBin aux = raiz->esquerda;
            free(raiz);
            return aux;
        }
        //Nó com 2 filhos, encontra o menor valor na subárvore direita
        ArvBin aux = encontrarMinimo(raiz->direita);
        raiz->valor = aux->valor;
        raiz->direita = excluir(raiz->direita, aux->valor);
    }
    return raiz;
}

int main(void) {
    ArvBin raiz = NULL;

    raiz = inserir_valor(raiz, 10);
    raiz = inserir_valor(raiz, 5);
    raiz = inserir_valor(raiz, 15);
    raiz = inserir_valor(raiz, 3);
    raiz = inserir_valor(raiz, 7);
    raiz = inserir_valor(raiz, 12);
    raiz = inserir_valor(raiz, 18);
    raiz = inserir_valor(raiz, 17);
    raiz = inserir_valor(raiz, 1);

    printf("Árvore estruturada:\n");
    imprimir_arvore(raiz, 0);

    // Teste de busca
    int valor_buscado = 4;
    ArvBin resultado = buscar_valor(raiz, valor_buscado);

    if (resultado != NULL) {
        printf("Valor %d encontrado na árvore.\n", resultado->valor);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valor_buscado);
    }

    // Teste excluindo valores
    raiz = excluir(raiz, 18);
    printf("Árvore após exclusão do valor 18:\n");
    printf("\n");
    imprimir_arvore(raiz, 0);
    raiz = excluir(raiz, 10);
    printf("Árvore após exclusão da raiz 10:\n");
    printf("\n");
    imprimir_arvore(raiz, 0);
    return 0;
}
