#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 5

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Gera automaticamente uma nova peça
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove a peça da frente da fila (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->fila[f->inicio];
    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças\n");

    if (filaVazia(f)) {
        printf("[Fila vazia]\n");
        return;
    }

    int i, pos;
    for (i = 0; i < f->quantidade; i++) {
        pos = (f->inicio + i) % TAM_FILA;
        printf("[%c %d] ", f->fila[pos].nome, f->fila[pos].id);
    }
    printf("\n");
}

int main() {
    Fila fila;
    int opcao;
    int contadorId = 0;

    srand(42); // Semente fixa para facilitar testes

    inicializarFila(&fila);

    // Inicializa a fila com peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorId++));
    }

    do {
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(contadorId++));
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
