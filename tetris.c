// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).
    
// ------------------------------------------------------------------------------------------------------------
// BLI, CONST e STRUCT

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5
#define MAX_PILHA 3

typedef struct {
    char tipo[50];
    int id;
} Peca;

typedef struct {
    Peca quant[MAX];
    int inicio, fim, total;
} Fila;

// 🧠 Nível Aventureiro: Pilha
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// ------------------------------------------------------------------------------------------------------------
// FUNÇÕES FILA

void comecarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

bool estaCheia(Fila *f) {
    return f->total == MAX;
}

bool estaVazia(Fila *f) {
    return f->total == 0;
}

void gerarPeca(Peca *pc, int nextId) {
    char tipos[] = {'I', 'O', 'T', 'L', 'S'};
    pc->tipo[0] = tipos[rand() % 5];
    pc->tipo[1] = '\0';
    pc->id = nextId;
}

void add(Fila *f, Peca pc) {
    if (estaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }
    f->quant[f->fim] = pc;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void tirar(Fila *f, Peca *pc) {
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    *pc = f->quant[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void verFila(Fila *f) {
    printf("Fila: ");
    if (estaVazia(f)) {
        printf("VAZIA\n");
        return;
    }
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->quant[idx].tipo, f->quant[idx].id);
    }
    printf("\n");
}

// ------------------------------------------------------------------------------------------------------------
// FUNÇÕES PILHA

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

bool pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

bool pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca pc) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = pc;
}

void pop(Pilha *p, Peca *pc) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }
    *pc = p->itens[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha: ");
    if (pilhaVazia(p)) {
        printf("VAZIA\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c, %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

// ------------------------------------------------------------------------------------------------------------
// MAIN

int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    int nextId = 1;

    comecarFila(&fila);
    inicializarPilha(&pilha);

    printf("Tetris Stack - Nível Aventureiro\n");

    // preencher fila inicial
    for (int i = 0; i < MAX; i++) {
        Peca nova;
        gerarPeca(&nova, nextId++);
        add(&fila, nova);
    }

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça (remover frente)\n");
        printf("2 - Enviar peça para reserva\n");
        printf("3 - Usar peça da reserva\n");
        printf("4 - Ver fila\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: {
                Peca jogada;
                tirar(&fila, &jogada);
                printf("Jogou: [%c, %d]\n", jogada.tipo, jogada.id);

                Peca nova;
                gerarPeca(&nova, nextId++);
                add(&fila, nova);
                break;
            }

            case 2: { // fila -> pilha
                if (pilhaCheia(&pilha)) {
                    printf("Reserva cheia!\n");
                    break;
                }

                Peca temp;
                tirar(&fila, &temp);
                push(&pilha, temp);
                printf("Enviado para reserva: [%c, %d]\n", temp.tipo, temp.id);

                Peca nova;
                gerarPeca(&nova, nextId++);
                add(&fila, nova);
                break;
            }

            case 3: { // pilha -> uso
                if (pilhaVazia(&pilha)) {
                    printf("Reserva vazia!\n");
                    break;
                }

                Peca temp;
                pop(&pilha, &temp);
                printf("Usou da reserva: [%c, %d]\n", temp.tipo, temp.id);
                break;
            }

            case 4:
                verFila(&fila);
                break;

            case 0:
                printf("Game Over!\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        verFila(&fila);
        mostrarPilha(&pilha);

    } while(opcao != 0);

    return 0;
}
