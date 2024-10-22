#include <stdio.h>
#include <stdlib.h>

//Árvore Treap (Árvore Binária de Busca + Heap)
//Criando a estrutura da árvore
typedef struct no {
    int valor;
    int prioridade;
    struct no *direita;
    struct no *esquerda;
}No;

// "Rotações" da Heap
//Rotação Simples à direita
No* RSD(No* y){
    No* x = y->esquerda;
    No* z = x->direita;

x->direita = y;
y->esquerda = z;
return x;
}

//Rotação Simples à esquerda
No* RSE(No* x){
    No* y = x->direita;
    No* z = y->esquerda;

y->esquerda = x;
x->direita = z;

return y;
}

No* inserir(No* raiz, int num, int prioridade){
    //Se a árvore estiver vazia, cria um novo nó
    if(raiz == NULL){
        No* novo = (No*)malloc(sizeof(struct no));
        novo->valor = num;
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->prioridade= prioridade; //Se quiser random (rand() % 100) + 1, vai de 1 a 100
        return novo;
    } else{ //Inserção da mesma maneira que a Binária, porém agora além de respeitar a ordem numerica, tbm respeitamos a prioridade
       if(num < raiz->valor){ //Se o novo nó for menor que a raiz, armazena na esquerda
        raiz->esquerda = inserir(raiz->esquerda, num, prioridade);
        if(raiz->esquerda && raiz->esquerda->prioridade > raiz->prioridade){ //Se a prioridade do nó inserido à esquerda for maior que a raiz é feito uma rotação à direita
            raiz = RSD(raiz);
        }
    } else if (num > raiz->valor){ //Se o novo nó for menor que a raiz, armazena na direita
        raiz->direita = inserir(raiz->direita, num, prioridade);
        if(raiz->direita && raiz->direita->prioridade > raiz-> prioridade){ //Se a prioridade do nó inserido à direita for maior que a raiz é feito uma rotação à esquerda
            raiz = RSE(raiz);
        }
    }
    return raiz;
}

}

No* remover(No* raiz, int num) {
    if (raiz == NULL) { //Arvore vazia
        return NULL;
    }

    // Encontra o nó a ser removido
    if (num < raiz->valor) { //Se o num for menor que a raiz procura na esquerda
        raiz->esquerda = remover(raiz->esquerda, num);
    } else if (num > raiz->valor) { //Se o num for menor que a raiz procura na direita
        raiz->direita = remover(raiz->direita, num);
    } else {
        // Nó encontrado

        // Caso 1: Nó folha (Sem filhos, só remover)
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2: Nó com um filho (está a direita ou a esquerda, o filho vira raiz)
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 3: Nó com dois filhos (Vira raiz quem tem a maior prioridade)
        // Rotaciona para manter a prioridade, removendo o nó recursivamente
        if (raiz->esquerda->prioridade > raiz->direita->prioridade) {
            raiz = RSD(raiz);
            raiz->direita = remover(raiz->direita, num);
        } else {
            raiz = RSE(raiz);
            raiz->esquerda = remover(raiz->esquerda, num);
        }
    }
    return raiz;
}

// Imprimindo a árvore
void imprimir(No *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        // Exibe o valor do nó e a prioridade
        printf("%d (Prioridade: %d)", raiz->valor, raiz->prioridade);

        imprimir(raiz->esquerda, nivel + 1);
    }
}
int main() {
    No* raiz = NULL;

    // Inserindo nós na Treap
    //Exercício feito na sala de aula
    raiz = inserir(raiz, 14,10);
    raiz = inserir(raiz, 12,5);
    raiz = inserir(raiz, 10,4);
    raiz = inserir(raiz, 9,7);
    raiz = inserir(raiz, 7,12);
    raiz = inserir(raiz, 16,9);
    raiz = inserir(raiz, 11,7);
    raiz = inserir(raiz, 18,2);
    raiz = inserir(raiz, 2,21);
    raiz = inserir(raiz, 31,18);

    // Imprimindo a Treap
    printf("Estrutura da Treap:\n");
    printf("Exercicio feito em sala de aula");
    imprimir(raiz,0);

    //Testando Remoção
    raiz = remover(raiz, 14);
    printf("\n\n\n");
    printf("Imprimindo depois de remover o 14, que tem 2 filhos, como 16 tem a maior prioridade vira raiz");
    imprimir(raiz,0);


    return 0;
}

