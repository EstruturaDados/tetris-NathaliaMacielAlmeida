#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    char tipo;  // tipo da peça (ex: 'I', 'O', 'T', 'L', 'Z')
    int id;     // identificador sequencial
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[TAM_FILA];
    int frente;
    int tras;
    int total;
} Fila;

// ---------- Funções da fila ----------

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->total = 0;
}

int filaVazia(Fila *f) {
    return (f->total == 0);
}

int filaCheia(Fila *f) {
    return (f->total == TAM_FILA);
}

// Gera uma peça com tipo aleatório e ID sequencial
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L', 'Z'};
    nova.tipo = tipos[rand() % 5];
    nova.id = id;
    return nova;
}

// Insere no final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠️ Fila cheia!\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->elementos[f->tras] = p;
    f->total++;
}

// Remove da frente da fila
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("\n⚠️ Fila vazia!\n");
        return removida;
    }
    removida = f->elementos[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->total--;
    return removida;
}

// Mostra o conteúdo da fila
void mostrarFila(Fila *f) {
    printf("\n🧱 Fila de Peças Futuras:\n");
    if (filaVazia(f)) {
        printf("   (vazia)\n");
        return;
    }
    for (int i = 0; i < f->total; i++) {
        int indice = (f->frente + i) % TAM_FILA;
        printf("   [%d] Tipo: %c | ID: %d\n", i+1, f->elementos[indice].tipo, f->elementos[indice].id);
    }
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int contadorID = 1;

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    int opcao;
    do {
        mostrarFila(&fila);
        printf("\n🎮 Menu:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            if (jogada.id != -1) {
                printf("\n🧩 Peça jogada: Tipo %c | ID %d\n", jogada.tipo, jogada.id);
                enqueue(&fila, gerarPeca(contadorID++));  // repõe nova peça no final
            }
        }

    } while (opcao != 0);

    printf("\n👋 Fim do jogo!\n");
    return 0;
}
