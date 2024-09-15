#include <stdio.h>
#include <stdlib.h>

// Árvore AVL
//Criando a estrutura da árvore
typedef struct no {
    int valor;
    struct no *direita;
    struct no *esquerda;
    int altura;
} No;

// Função para descobrir a altura do nó
int alturaNo(No *no) {
    if (no == NULL) // Se a árvore estiver vazia não tem altura
    {
        return -1;
    } else {
        return no->altura;
    }
}

// Função para descobrir o Fator de Balanceamento = (esq - dir)
int fatorBalanceamento(No *no) {
    if (no) {
        return alturaNo(no->esquerda) - alturaNo(no->direita);
    } else {
        return 0;
    }
}

// Função para imprimir a árvore AVL
void imprimir(No *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        // Exibe o valor do nó e o fator de balanceamento
        printf("%d (FB=%d)", raiz->valor, fatorBalanceamento(raiz));
        imprimir(raiz->esquerda, nivel + 1);
    }
}

// Função para criar um novo nó
No* novoNo(int num) {
    No *novo = (No*) malloc(sizeof(No)); //Armazena espaço de memória para o nó
    if (novo) {
        novo->valor = num;
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->altura = 0;
    } else {
        printf("Não foi possível criar o novo nó");
    }
    return novo;
}

// Função para descobrir o maior valor entre subárvores
int maiorValor(int esq, int dir) {
//    if(esq>dir)
//        return esq;
//    else
//        return dir;
    return (esq > dir) ? esq : dir; //esq é maior que a direita, se sim retorna esq, senão dir.
}

// Rotação Simples à Esquerda
No* RSEsquerda(No *velhaRaiz) {

    //Preparando as variáveis
    No *novaRaiz = velhaRaiz->direita; //NovaRaiz será o nó que estava a direita da raiz
    No *subArvoreEsqNovaRaiz = novaRaiz->esquerda; //A subArvore é o que estava a esquerda da novaRaiz

    //Realizando a Rotação
    novaRaiz->esquerda = velhaRaiz; //A velhaRaiz ficará na esquerda da novaRaiz
    velhaRaiz->direita = subArvoreEsqNovaRaiz; //A subArvore ficará à direita da velhaRaiz

    velhaRaiz->altura = maiorValor(alturaNo(velhaRaiz->esquerda), alturaNo(velhaRaiz->direita)) + 1;
    novaRaiz->altura = maiorValor(alturaNo(novaRaiz->esquerda), alturaNo(novaRaiz->direita)) + 1;

    return novaRaiz;
}

// Rotação Simples à Direita
No* RSDireita(No *velhaRaiz) {

    //Preparando as variáveis
    No *novaRaiz = velhaRaiz->esquerda; //NovaRaiz será o nó que estavá à esquerda da velhaRaiz
    No *subArvoreDirNovaRaiz = novaRaiz->direita; //A subArvore ficará à esquerda da novaRaiz

    //Realizando as Rotação
    novaRaiz->direita = velhaRaiz; //A velhaRaiz ficará a direita da novaRaiz
    velhaRaiz->esquerda = subArvoreDirNovaRaiz; //A subArvore ficará à esquerda da velhaRaiz

    velhaRaiz->altura = maiorValor(alturaNo(velhaRaiz->esquerda), alturaNo(velhaRaiz->direita)) + 1;
    novaRaiz->altura = maiorValor(alturaNo(novaRaiz->esquerda), alturaNo(novaRaiz->direita)) + 1;

    return novaRaiz;
}

// Rotação Dupla à Esquerda (RSD + RSE)
No* RDEsquerda(No *velhaRaiz) {

    // Primeiro é feito a rotação à direita no filho esquerdo
    velhaRaiz->direita = RSDireita(velhaRaiz->direita);
    // Depois é feita a rotação à esquerda na raiz
    return RSEsquerda(velhaRaiz);
}

// Rotação Dupla à Direita (RSE + RSD)
No* RDDireita(No *velhaRaiz) {
    // Primeiro é feito a rotação à esquerda no filho direito
    velhaRaiz->esquerda = RSEsquerda(velhaRaiz->esquerda);
    // Depois é feita a rotação à direita na raiz
    return RSDireita(velhaRaiz);
}

// Função para balancear a árvore (tolerados = -1, 0 ou 1)
No* balancear(No* raiz) {
    int fB = fatorBalanceamento(raiz);

    // Rotação à esquerda
    if (fB < -1 && fatorBalanceamento(raiz->direita) <= 0)
        raiz = RSEsquerda(raiz);

    // Rotação à direita
    else if (fB > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
        raiz = RSDireita(raiz);

    // Rotação Dupla à esquerda
    else if (fB < -1 && fatorBalanceamento(raiz->direita) > 0)
        raiz = RDEsquerda(raiz);

    // Rotação Dupla à direita
    else if (fB > 1 && fatorBalanceamento(raiz->esquerda) < 0)
        raiz = RDDireita(raiz);

    return raiz;
}

//Encontrando o menor valor da Árvore
No* encontrarMinimo(No *raiz) {
    No* atual = raiz;

    // Percorre a subárvore esquerda até encontrar o menor
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

// Encontrando o maior valor da Árvore
No* encontrarMaximo(No *raiz) {
    No* atual = raiz;

    // Percorre a subárvore direita até encontrar o maior
    while (atual && atual->direita != NULL)
        atual = atual->direita;

    return atual;
}

// Função para inserir valores na árvore
No* inserir(No *raiz, int num) {
    if (raiz == NULL) //Se a árvore estiver vazia o primeiro nó é criado
        return novoNo(num);
    else {
        if (num < raiz->valor) //Se esse novo nó for menor que a raiz armazena na esquerda
            raiz->esquerda = inserir(raiz->esquerda, num);
        else if (num > raiz->valor) //Se o novo nó for maior que a raiz armazena na direita
            raiz->direita = inserir(raiz->direita, num);
        else {
            printf("\nValor já inserido\n");
            return raiz;
        }
    }

    // Atualizando a altura do nó após a inserção
    raiz->altura = maiorValor(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    // Balanceando a árvore após a inserção
    return balancear(raiz);
}

//Função para Remover valores da Árvore
No* remover(No* raiz, int num){
    if(raiz == NULL) //Se a árvore estiver vazia, não há nada para excluir
    {
        printf("Valor não encontrado");
        return NULL;
    }
    if(num < raiz->valor)//Procura na esquerda da raiz
    {
        raiz->esquerda = remover(raiz->esquerda, num);
    }
    else if(num > raiz->valor)//Procura na direita da raiz
    {
        raiz->direita = remover(raiz->direita, num);
    }
    else{
        //Caso 1: Nó folha ou com apenas um filho
        if(raiz->esquerda == NULL) //Se tiver apenas filhos à direita
        {
            No* valor = raiz->direita;
            free(raiz);
            return valor;
        }
        else if(raiz->direita == NULL) //Se tiver apenas filhos à esquerda
        {
            No* valor = raiz->esquerda;
            free(raiz);
            return valor;
        }

        //Caso 2: Nó com 2 filhos
        if(alturaNo(raiz->esquerda) >= alturaNo(raiz->direita))
        {
            No* temp = encontrarMaximo(raiz->esquerda);
            raiz->valor = temp->valor;
            raiz->esquerda = remover(raiz->esquerda, temp->valor);
        }
        else
        {
            No* temp = encontrarMinimo(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }
    return balancear(raiz);
}

No* buscar_valor(No* raiz, int num) {
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


int main() {
    //Realizando o exercício previamente feito em sala de aula, no papel

    No *raiz = NULL; //Inicia a árvore com uma raiz vazia

    //Adiciona valores
    raiz = inserir(raiz, 50); //Primeiro valor da árvore = raiz
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 64);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 18);
    raiz = inserir(raiz, 66);
    raiz = inserir(raiz, 38);
    raiz = inserir(raiz, 95);
    raiz = inserir(raiz, 58);
    raiz = inserir(raiz, 59);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 68);
    raiz = inserir(raiz, 39);
    raiz = inserir(raiz, 62);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 43);
    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 67);
    raiz = inserir(raiz, 34);
    raiz = inserir(raiz, 35);


    imprimir(raiz, 0); //Visualização final
    printf("\n");
    printf("-------------------------------------------------------\n");

    //Teste de Busca
    int valor_buscado = 7;
    No* resultado = buscar_valor(raiz, valor_buscado);

    if (resultado != NULL) {
        printf("Valor %d encontrado na árvore.\n", resultado->valor);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valor_buscado);
    }
    printf("\n");
    printf("-------------------------------------------------------\n");

    //Removendo o 50
    raiz = remover(raiz, 50);
    imprimir(raiz, 0);

    printf("\n");
    printf("-------------------------------------------------------");


    //Removendo o 95
    raiz = remover(raiz, 95);
     imprimir(raiz, 0);

    printf("\n");
    printf("-------------------------------------------------------");

    //Removendo o 70
    raiz = remover(raiz, 70);
     imprimir(raiz, 0);

    printf("\n");
    printf("-------------------------------------------------------");

    return 0;
}

