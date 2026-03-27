// 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

// ------------------------------------------------------------------------------------------------------------
// BLI, CONST e STRUCT

    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <time.h>
    #define MAX 5

    typedef struct {
        char tipo[50];
        int id;
    } Peca;

    typedef struct {
        Peca quant[MAX];
        int inicio, fim, total;
    } Fila;

// ------------------------------------------------------------------------------------------------------------
// FUNÇÕES

    void comecarFila(Fila *f) { // inicia a fila
        f->inicio = 0;
        f->fim = 0;
        f->total = 0;
    }

    bool estaCheia(Fila *f) { // está cheia?
        return f->total == MAX;
    }

    bool estaVazia(Fila *f) { // está vazia?
        return f->total == 0;
    }

    void gerarPeca(Peca *pc, int nextId) { // gerar peca aleatoria
        char tipos[] = {'I', 'O', 'T', 'L', 'S'};
        pc->tipo[0] = tipos[rand() % 5];
        pc->tipo[1] = '\0';
        pc->id = nextId;
    }

    void add(Fila *f, Peca pc) { // inserir
        if (estaCheia(f)) {
            printf("Fila cheia! Impossível inserir.\n");
            return;
        }
        f->quant[f->fim] = pc;
        f->fim = (f->fim + 1) % MAX;
        f->total++;
    }

    void tirar(Fila *f, Peca *pc) { // remover
        if (estaVazia(f)) {
            printf("Fila vazia! Nada para remover.\n");
            return;
        }
        *pc = f->quant[f->inicio];
        f->inicio = (f->inicio + 1) % MAX;
        f->total--;
    }

    void verFila(Fila *f) { // mostrar
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
// MAIN

    int main() {
        srand(time(NULL));
        Fila fila;
        int nextId = 1;
        comecarFila(&fila);
        
        printf("Tetris Stack - Nível Novato\n");
        for (int i = 0; i < MAX; i++) {
            Peca nova;
            gerarPeca(&nova, nextId++);
            add(&fila, nova);
        }
        
        int opcao;
        do {
            printf("\n=== MENU ===\n");
            printf("1 - Jogar peça (remover frente)\n");
            printf("2 - Ver fila\n");
            printf("0 - Sair\n");
            printf("Opção: ");
            scanf("%d", &opcao);
            
            switch(opcao) {
                case 1: {
                    Peca jogada;
                    tirar(&fila, &jogada);
                    printf("Jogou: [%c, %d]\n", jogada.tipo, jogada.id);
                    
                    // Adiciona nova peça automaticamente
                    Peca nova;
                    gerarPeca(&nova, nextId++);
                    add(&fila, nova);
                    printf("Nova peça: [%c, %d]\n", nova.tipo, nova.id);
                    break;
                }
                case 2:
                    verFila(&fila);
                    break;
                case 0:
                    printf("Game Over!\n");
                    break;
                default:
                    printf("Opção inválida!\n");
            }
            verFila(&fila);
        } while(opcao != 0);
        
        return 0;
    }

// ------------------------------------------------------------------------------------------------------------