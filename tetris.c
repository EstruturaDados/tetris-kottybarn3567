// 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
    
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
// FUNÇÕES DE INTEGRAÇÃO

void trocarFrenteFilaTopoPilha(Fila *fila, Pilha *pilha) {
    if (estaVazia(fila)) {
        printf("Nao e possivel trocar: fila vazia!\n");
        return;
    }
    if (pilhaVazia(pilha)) {
        printf("Nao e possivel trocar: pilha vazia!\n");
        return;
    }
    
    // Troca direta usando índices
    Peca frenteFila = fila->quant[fila->inicio];
    Peca topoPilha = pilha->itens[pilha->topo];
    
    fila->quant[fila->inicio] = topoPilha;
    pilha->itens[pilha->topo] = frenteFila;
    
    printf("Troca realizada: Fila[%d] <-> Pilha[topo]\n", frenteFila.id);
    printf("  Frente fila era [%c,%d], agora [%c,%d]\n", 
           frenteFila.tipo, frenteFila.id, topoPilha.tipo, topoPilha.id);
    printf("  Topo pilha era [%c,%d], agora [%c,%d]\n", 
           topoPilha.tipo, topoPilha.id, frenteFila.tipo, frenteFila.id);
}

void trocarTresPrimeiros(Fila *fila, Pilha *pilha) {
    if (fila->total < 3) {
        printf("Nao e possivel trocar: fila tem menos de 3 pecas (%d)\n", fila->total);
        return;
    }
    if (pilha->topo != 2) { // exatamente 3 peças (topo = 2)
        printf("Nao e possivel trocar: pilha deve ter exatamente 3 pecas (tem %d)\n", pilha->topo + 1);
        return;
    }
    
    // Salva os 3 primeiros da fila (considerando circularidade)
    Peca tresFila[3];
    int idx = fila->inicio;
    for (int i = 0; i < 3; i++) {
        tresFila[i] = fila->quant[idx];
        idx = (idx + 1) % MAX;
    }
    
    // Salva os 3 da pilha (topo para baixo)
    Peca tresPilha[3];
    for (int i = 0; i < 3; i++) {
        tresPilha[i] = pilha->itens[2 - i]; // topo=2,1,0
    }
    
    // Coloca pilha na fila
    idx = fila->inicio;
    for (int i = 0; i < 3; i++) {
        fila->quant[idx] = tresPilha[i];
        idx = (idx + 1) % MAX;
    }
    
    // Coloca fila na pilha (mantendo ordem LIFO)
    for (int i = 2; i >= 0; i--) {
        pilha->itens[i] = tresFila[i];
    }
    pilha->topo = 2;
    
    printf("Troca de 3 pecas realizada com sucesso!\n");
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

    printf("Tetris Stack - Nível Mestre\n");

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
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("6 - Ver fila e pilha\n");
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
                trocarFrenteFilaTopoPilha(&fila, &pilha);
                break;

            case 5:
                trocarTresPrimeiros(&fila, &pilha);
                break;

            case 6:
                verFila(&fila);
                mostrarPilha(&pilha);
                break;

            case 0:
                printf("Game Over!\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        // Mostra estado atual (exceto na opção 6)
        if (opcao != 6 && opcao != 0) {
            verFila(&fila);
            mostrarPilha(&pilha);
        }

    } while(opcao != 0);

    return 0;
}