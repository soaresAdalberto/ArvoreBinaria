#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;

typedef struct arvore {
    No *raiz;
} Arvore;

void inicializa_arvore(Arvore *arvore) {
    arvore->raiz = NULL;
}

void insere_no(No **no, int valor) {
    if (*no == NULL) {
        *no = (No*) malloc(sizeof(No));
        (*no)->valor = valor;
        (*no)->esquerda = NULL;
        (*no)->direita = NULL;
    } else {
        if (valor < (*no)->valor) {
            insere_no(&((*no)->esquerda), valor);
        } else {
            insere_no(&((*no)->direita), valor);
        }
    }
}

void insere_valor(Arvore *arvore, int valor) {
    insere_no(&(arvore->raiz), valor);
}

int busca_no(No *no, int valor) {
    if (no == NULL) {
        return 0;
    } else {
        if (no->valor == valor) {
            return 1;
        } else if (valor < no->valor) {
            return busca_no(no->esquerda, valor);
        } else {
            return busca_no(no->direita, valor);
        }
    }
}

int busca_valor(Arvore *arvore, int valor) {
    return busca_no(arvore->raiz, valor);
}

int altura_no(No *no) {
    if (no == NULL) {
        return -1;
    } else {
        int altura_esquerda = altura_no(no->esquerda);
        int altura_direita = altura_no(no->direita);
        if (altura_esquerda > altura_direita) {
            return altura_esquerda + 1;
        } else {
            return altura_direita + 1;
        }
    }
}

int altura_arvore(Arvore *arvore) {
    return altura_no(arvore->raiz);
}

No *busca_menor(No *no) {
    No *atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No *remove_no(No *no, int valor) {
    if (no == NULL) {
        return NULL;
    }
    if (valor < no->valor) {
        no->esquerda = remove_no(no->esquerda, valor);
    } else if (valor > no->valor) {
        no->direita = remove_no(no->direita, valor);
    } else {
        if (no->esquerda == NULL) {
            No *temp = no->direita;
            free(no);
            return temp;
        } else if (no->direita == NULL) {
            No *temp = no->esquerda;
            free(no);
            return temp;
        }
        No *temp = busca_menor(no->direita);
        no->valor = temp->valor;
        no->direita = remove_no(no->direita, temp->valor);
    }
    return no;
}

void remove_valor(Arvore *arvore, int valor) {
    arvore->raiz = remove_no(arvore->raiz, valor);
}

void imprime_pre_ordem(No *no) {
    if (no != NULL) {
        printf("%d ", no->valor);
        imprime_pre_ordem(no->esquerda);
        imprime_pre_ordem(no->direita);
    }
}

void imprime_in_ordem(No *no) {
    if (no != NULL) {
        imprime_in_ordem(no->esquerda);
        printf("%d ", no->valor);
        imprime_in_ordem(no->direita);
    }
}

void imprime_pos_ordem(No *no) {
    if (no != NULL) {
        imprime_pos_ordem(no->esquerda);
        imprime_pos_ordem(no->direita);
        printf("%d ", no->valor);
    }
}

int main() {
    Arvore arvore;
    int opcao, valor;
    inicializa_arvore(&arvore);

do {
    printf("\n\nEscolha uma opcao:\n");
    printf("1 - Inserir valor\n");
    printf("2 - Buscar valor\n");
    printf("3 - Altura da arvore\n");
    printf("4 - Remover valor\n");
    printf("5 - Imprimir em Pre-Ordem\n");
    printf("6 - Imprimir em In-Ordem\n");
    printf("7 - Imprimir em Pos-Ordem\n");
    printf("0 - Sair\n");

    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("\nDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            insere_valor(&arvore, valor);
            break;

        case 2:
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &valor);
            if (busca_valor(&arvore, valor)) {
                printf("\nValor encontrado!\n");
            } else {
                printf("\nValor nao encontrado!\n");
            }
            break;

        case 3:
            printf("\nAltura da arvore: %d\n", altura_arvore(&arvore));
            break;

        case 4:
            printf("\nDigite o valor a ser removido: ");
            scanf("%d", &valor);
            remove_valor(&arvore, valor);
            break;

        case 5:
            printf("\nImprimindo em Pre-Ordem: ");
            imprime_pre_ordem(arvore.raiz);
            printf("\n");
            break;

        case 6:
            printf("\nImprimindo em In-Ordem: ");
            imprime_in_ordem(arvore.raiz);
            printf("\n");
            break;

        case 7:
            printf("\nImprimindo em Pos-Ordem: ");
            imprime_pos_ordem(arvore.raiz);
            printf("\n");
            break;

        case 0:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
    }
} while (opcao != 0);

return 0;
}