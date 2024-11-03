#include <stdio.h>
#include <stdlib.h>

// Definir o máximo de chaves e o mínimo de chaves em um nó (nesse caso ordem 2)
#define MAX 2
#define MIN 1

// Estrutura do nó da árvore B
struct ArvoreB {
    int valor[MAX + 1], contador; // valor armazena as chaves, contador armazena o número de chaves
    struct ArvoreB* link[MAX + 1]; // link armazena os ponteiros para os filhos
};

struct ArvoreB* raiz; // raiz da árvore

// Função para criar um novo nó
struct ArvoreB* criarNo(int valor, struct ArvoreB* filho) {
    struct ArvoreB* novoNo;
    novoNo = (struct ArvoreB*)malloc(sizeof(struct ArvoreB)); // aloca memória para o novo nó
    novoNo->valor[1] = valor; // insere o valor no nó
    novoNo->contador = 1; // inicia a contagem de chaves com 1
    novoNo->link[0] = raiz; // seta o primeiro link para a raiz
    novoNo->link[1] = filho; // seta o segundo link para o filho
    return novoNo; // retorna o novo nó
}

// Função para adicionar um valor ao nó
void adicionaNo(int valor, int pos, struct ArvoreB* no, struct ArvoreB* filho) {
    int j = no->contador;
    while (j > pos) { // move valores e links para abrir espaço para o novo valor
        no->valor[j + 1] = no->valor[j];
        no->link[j + 1] = no->link[j];
        j--;
    }
    no->valor[j + 1] = valor; // insere o novo valor na posição correta
    no->link[j + 1] = filho; // ajusta o link do filho
    no->contador++; // incrementa a contagem de chaves
}

// Função para dividir o nó
void separaArray(int valor, int* pval, int pos, struct ArvoreB* no, struct ArvoreB* filho, struct ArvoreB** novoNo) {
    int median, j;
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *novoNo = (struct ArvoreB*)malloc(sizeof(struct ArvoreB)); // aloca memória para o novo nó
    j = median + 1;
    while (j <= MAX) { // move metade das chaves para o novo nó
        (*novoNo)->valor[j - median] = no->valor[j];
        (*novoNo)->link[j - median] = no->link[j];
        j++;
    }
    no->contador = median; // ajusta a contagem do nó original
    (*novoNo)->contador = MAX - median; // ajusta a contagem do novo nó

    if (pos <= MIN)
        adicionaNo(valor, pos, no, filho); // adiciona valor ao nó original se a posição for menor ou igual ao mínimo
    else
        adicionaNo(valor, pos - median, *novoNo, filho); // adiciona valor ao novo nó se a posição for maior que o mínimo

    *pval = no->valor[no->contador]; // atualiza o valor promovido
    (*novoNo)->link[0] = no->link[no->contador]; // ajusta o link do novo nó
    no->contador--; // decrementa a contagem do nó original
}

// Função para inserir um valor
int setValueInNode(int valor, int* pval, struct ArvoreB* no, struct ArvoreB** filho) {
    int pos;
    if (!no) { // se o nó estiver vazio
        *pval = valor;
        *filho = NULL;
        return 1;
    }
    if (valor < no->valor[1]) {
        pos = 0; // encontra a posição correta para o valor
    } else {
        for (pos = no->contador; (valor < no->valor[pos] && pos > 1); pos--);
        if (valor == no->valor[pos]) {
            return 0; // se o valor já existir, retorna 0
        }
    }
    if (setValueInNode(valor, pval, no->link[pos], filho)) { // insere o valor no filho(array) adequado
        if (no->contador < MAX) {
            adicionaNo(*pval, pos, no, *filho); // adiciona valor se o (array) não estiver cheio
        } else {
            separaArray(*pval, pval, pos, no, *filho, filho); // divide o (array) se estiver cheio
            return 1;
        }
    }
    return 0;
}

// Função para inserir um valor na árvore
void insere(int valor) {
    int flag, i;
    struct ArvoreB* filho;

    flag = setValueInNode(valor, &i, raiz, &filho);
    if (flag)
        raiz = criarNo(i, filho); // cria um novo nó raiz se necessário, se o array ficar cheio e um nó precisar se mover
}

// Função para buscar um valor
void busca(int valor, int* pos, struct ArvoreB* no) {
    if (!no) {
        return;
    }
    if (valor < no->valor[1]) {
        *pos = 0; // encontra a posição correta para buscar o valor
    } else {
        for (*pos = no->contador; (valor < no->valor[*pos] && *pos > 1); (*pos)--);
        if (valor == no->valor[*pos]) {
            return;
        }
    }
    busca(valor, pos, no->link[*pos]); // busca recursivamente
}

// Função para imprimir a árvore
void imprimir(struct ArvoreB* no, int nivel) {
    int i;
    if (no) {
        for (i = no->contador; i > 0; i--) {
            imprimir(no->link[i], nivel + 1); // imprime os filhos da direita
            for (int j = 0; j < nivel; j++) {
                printf("  ");
            }
            printf("%d\n", no->valor[i]); // imprime o valor do nó
        }
        imprimir(no->link[i], nivel + 1); // imprime os filhos da esquerda
    }
}

//Exercício Feito na sala de aula
//{18,25,19,16,17,22,31,12,14,15,23,32,6,40,7}
int main() {
    insere(18);
    insere(25);
    insere(19);
    insere(16);
    insere(17);
    insere(22);
    insere(31);
    insere(12);
    insere(14);
    insere(15);
    insere(23);
    insere(32);
    insere(6);
    insere(40);
    insere(7);

    printf("Árvore B:\n");
    imprimir(raiz, 0);

    return 0;
}
