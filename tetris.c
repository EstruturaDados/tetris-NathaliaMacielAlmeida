#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

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

// -------- Pilha Linear --------
typedef struct {
    Peca elementos[TAM_PILHA];
    int topo;
} Pilha;

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

// ---------- Funções da Pilha ----------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

int pilhaCheia(Pilha *p) {
    return (p->topo == TAM_PILHA - 1);
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("\n⚠️ Pilha cheia! Não é possível enviar mais peças para a reserva.\n");
        return;
    }
    p->topo++;
    p->elementos[p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca removida = {'-', -1};
    if (pilhaVazia(p)) {
        printf("\n⚠️ Pilha vazia! Nenhuma peça na reserva.\n");
        return removida;
    }
    removida = p->elementos[p->topo];
    p->topo--;
    return removida;
}

void mostrarPilha(Pilha *p) {
    printf("\n🎒 Pilha de Reserva:\n");
    if (pilhaVazia(p)) {
        printf("   (vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("   [%d] Tipo: %c | ID: %d\n", i+1, p->elementos[i].tipo, p->elementos[i].id);
    }
}

// ---------- Função principal ----------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contadorID = 1;

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    int opcao;
    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\n🎮 Menu:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Enviar peça da fila para a reserva (pilha)\n");
        printf("3 - Usar peça da reserva (remover do topo da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            if (jogada.id != -1) {
                printf("\n🧩 Peça jogada: Tipo %c | ID %d\n", jogada.tipo, jogada.id);
                enqueue(&fila, gerarPeca(contadorID++));
            }
        }

        else if (opcao == 2) {
            if (filaVazia(&fila)) {
                printf("\n⚠️ Fila vazia! Não há peça para enviar.\n");
            } else if (pilhaCheia(&pilha)) {
                printf("\n⚠️ Pilha cheia! Libere espaço antes.\n");
            } else {
                Peca enviada = dequeue(&fila);
                push(&pilha, enviada);
                printf("\n📦 Peça enviada para reserva: Tipo %c | ID %d\n", enviada.tipo, enviada.id);
                enqueue(&fila, gerarPeca(contadorID++));
            }
        }

        else if (opcao == 3) {
            Peca usada = pop(&pilha);
            if (usada.id != -1) {
                printf("\n🎯 Peça usada da reserva: Tipo %c | ID %d\n", usada.tipo, usada.id);
            }
        }

    } while (opcao != 0);

    printf("\n👋 Fim do jogo!\n");
    return 0;
}