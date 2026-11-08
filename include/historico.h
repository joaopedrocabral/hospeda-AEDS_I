#ifndef HISTORICO_H
#define HISTORICO_H

#include <time.h>

// Cada no guarda uma operacao realizada.
typedef struct Registro {
    int id;
    char modulo[30];
    char operacao[30];
    char descricao[150];
    time_t dataHora;
    struct Registro *proximo;
} Registro;

// A pilha guarda o endereco do registro mais recente.
typedef struct {
    Registro *topo;
    int proximoId;
} PilhaHistorico;

void iniciarHistorico(PilhaHistorico *pilha);
int registrarOperacao(PilhaHistorico *pilha, const char *modulo,
                     const char *operacao, const char *descricao);
void listarHistorico(const PilhaHistorico *pilha);
void buscarHistorico(const PilhaHistorico *pilha, int id);
int desempilharHistorico(PilhaHistorico *pilha); // Remocao interna, sem menu.
void liberarHistorico(PilhaHistorico *pilha);

#endif
