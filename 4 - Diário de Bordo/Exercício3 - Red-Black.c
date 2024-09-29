#include <stdio.h>
#include <stdlib.h>

// Definindo as cores
#define VERMELHO 0
#define PRETO 1

// Definindo a estrutura da árvore
typedef struct no {
    int valor; //Valor que será armazenado
    int cor; //Vermelho ou Preto
    struct no *esquerda;
    struct no *direita;
    struct no *pai;
} No;

// Criando um novo nó
No *criarNo(int num) {
    No *novoNo = (No *)malloc(sizeof(No)); //Alocando memória para o novo nó
    novoNo->valor = num;
    novoNo->cor = VERMELHO; //Todo novo nó é vermelho
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL; //O novo não não tem filhos à direita e esquerda, nem pai
    return novoNo;
}

// Rotação à esquerda
void RSEsquerda(No **raiz, No *x) {
    No *y = x->direita; //y = filho direito de x
    x->direita = y->esquerda; //O filho direito de x passa a ser o filho esquerdo de y
    if (y->esquerda != NULL) //Se o filho esquerdo de y não for NULL
        y->esquerda->pai = x; //O seu pai vira o x
    y->pai = x->pai; //O pai de y = pai de x
    if (x->pai == NULL) //Se o x for a raiz (não tiver pai)
        *raiz = y; //y se torna raiz
    else if (x == x->pai->esquerda) //Se x é o filho esquerdo
        x->pai->esquerda = y; //y fica no seu lugar
    else
        x->pai->direita = y; //Se x é o filho direito, y fica no seu lugar
    y->esquerda = x; //x vira o filho esquerdo de y
    x->pai = y; //y vira o pai de x
}

// Rotação à direita
void RSDireita(No **raiz, No *x) {
    No *y = x->esquerda; //y = filho esquerdo de x
    x->esquerda = y->direita; //O filho de esquerdo de x virá o filho direito de y
    if (y->direita != NULL) //Se O filho direito de y não for NULL
        y->direita->pai = x; //O seu pai virá o x
    y->pai = x->pai; //O pai de y = pai de x
    if (x->pai == NULL) //Se o pai de x for NULL
        *raiz = y; //y se torna raiz
    else if (x == x->pai->direita) //Se x é o filho direito
        x->pai->direita = y; //y fica no seu lugar
    else
        x->pai->esquerda = y; //Se x é o filho esquerdo, y fica no seu lugar
    y->direita = x; //x virá filho direito de x
    x->pai = y; //y virá pai de x
}

// Corrigir as cores após a inserção
void corrigir(No **raiz, No *z) {
    while (z != *raiz && z->pai->cor == VERMELHO) { //Enquanto z não for a raiz e a cor de seu pai for vermelha
        if (z->pai == z->pai->pai->esquerda) { //Se o pai de z for o filho esquerdo de seu avô
            No *y = z->pai->pai->direita; //y = tio de z (filho direito de seu avô)
            if (y != NULL && y->cor == VERMELHO) { // O tio de z é vermelho
                z->pai->cor = PRETO; // O pai de z fica preto
                y->cor = PRETO; //O tio de z fica preto
                z->pai->pai->cor = VERMELHO; //O avô de z fica vermelho
                z = z->pai->pai; //Verfica no nível acima
            } else {
                if (z == z->pai->direita) { //z é o filho direito
                    z = z->pai; //z vira pai de z
                    RSEsquerda(raiz, z); //Rotação a esquerda é feita no pai de z
                }
                z->pai->cor = PRETO; //O pai de z fica preto
                z->pai->pai->cor = VERMELHO; //O avô de z fica vermelho
                RSDireita(raiz, z->pai->pai); //Rotação a direira é feita no avô de z
            }
        } else {
            No *y = z->pai->pai->esquerda; //y = tio de z (filho esquerdo do avô)
            if (y != NULL && y->cor == VERMELHO) { // tio de z é vermelho
                z->pai->cor = PRETO; //pai de zfica preto
                y->cor = PRETO; //tio de z fica preto
                z->pai->pai->cor = VERMELHO; //avô de z fica vermelho
                z = z->pai->pai; //Verfica no nível acima
            } else {
                if (z == z->pai->esquerda) { //z é o filho esquerdo
                    z = z->pai; // z se torna pai de z
                    RSDireita(raiz, z); //Rotação à direita é feita no pai de z
                }
                z->pai->cor = PRETO; //O pai do z fica preto
                z->pai->pai->cor = VERMELHO; //O avô de z fica vermelho
                RSEsquerda(raiz, z->pai->pai); //Rotação à esquerda é feita no avô
            }
        }
    }
    (*raiz)->cor = PRETO; //A raiz da árvore SEMPRE deve ser preta
}

// Inserindo valores
void inserir(No **raiz, int valor) {
    No *z = criarNo(valor); //Cria o novo nó
    No *y = NULL;
    No *x = *raiz; //x é a raiz da árvore

    while (x != NULL) { //Enquanto a raiz for diferente de NULL
        y = x; //y = pai de x
        if (z->valor < x->valor) //Se o valor de z for menor que o valor de x
            x = x->esquerda; //x é o filho esquerdo
        else //Se o valor de z for maior que o valor de x
            x = x->direita; //x é o filho direito
    }
    z->pai = y; //y = pai de z
    if (y == NULL) //Se y for NULL a árvore está vazia
        *raiz = z; //z é a nova raiz
    else if (z->valor < y->valor)//Se o valor de z for menor que o valor de y
        y->esquerda = z; //z é o filho esquerdo de y
    else //Se o valor de z for maior que o valor de x
        y->direita = z; //z é o filho direito de y

    corrigir(raiz, z); //função para corrigir as cores
}

// Função para imprimir a árvore
void imprimir(No *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        // Exibe o valor do nó e a cor
        printf("%d (%s)", raiz->valor, raiz->cor == VERMELHO ? "Vermelho" : "Preto");
        //A cor do nó é vermelha, se for retorne, senão retorne preto
        imprimir(raiz->esquerda, nivel + 1);
    }
}


    //Função de Busca
    No* buscar_valor(No *raiz, int num) {
        // Se a árvore estiver vazia ou o valor for encontrado de primeira (O(1))
        if ((raiz == NULL) || (raiz->valor == num))
        return raiz;

        // Se o valor for menor que a raiz, procurar na esquerda
        if (num < raiz->valor) {
        return buscar_valor(raiz->esquerda, num);
        // Se o valor for maior que a raiz, procurar na direita
    } else {
        return buscar_valor(raiz->direita, num);;
    }
}


int main(void) {
    //Exercício feito em sala de aula
    No *raiz = NULL;
    inserir(&raiz,50);
    inserir(&raiz,40);
    inserir(&raiz,30);
    inserir(&raiz,25 );
    inserir(&raiz,27 );
    inserir(&raiz,60 );
    inserir(&raiz,80 );
    inserir(&raiz,10 );
    inserir(&raiz,75 );
    inserir(&raiz,95 );
    inserir(&raiz,15 );
    inserir(&raiz,12 );
    inserir(&raiz,65);
    inserir(&raiz,35 );
    inserir(&raiz,55 );

    No *resultado = buscar_valor(raiz, 12);
    if (resultado != NULL)
        printf("Valor %d encontrado na árvore.\n", resultado->valor);
    else
        printf("Valor não encontrado na árvore.\n");

    imprimir(raiz, 0);

    return 0;
}
