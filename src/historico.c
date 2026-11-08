#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/historico.h"

// Comeca com a pilha vazia.
void iniciarHistorico(PilhaHistorico *pilha) {
    pilha->topo = NULL;
    pilha->proximoId = 1;
}

// Adiciona um registro novo no topo da pilha.
int registrarOperacao(PilhaHistorico *pilha, const char *modulo,
                     const char *operacao, const char *descricao) {
    Registro *novo = malloc(sizeof(Registro));
    if (novo == NULL) return 0;

    novo->id = pilha->proximoId;
    snprintf(novo->modulo, sizeof(novo->modulo), "%s", modulo);
    snprintf(novo->operacao, sizeof(novo->operacao), "%s", operacao);
    snprintf(novo->descricao, sizeof(novo->descricao), "%s", descricao);
    novo->dataHora = time(NULL); // Pega data e hora do computador.
    novo->proximo = pilha->topo; // O novo aponta para o antigo topo.
    pilha->topo = novo;          // O novo passa a ser o topo.
    pilha->proximoId++;
    return 1;
}

// Mostra um registro com data e horario.
static void mostrarRegistro(const Registro *r) {
    char data[30];
    struct tm *horario = localtime(&r->dataHora);
    if (horario != NULL) {
        strftime(data, sizeof(data), "%d/%m/%Y %H:%M:%S", horario);
    } else {
        snprintf(data, sizeof(data), "Data indisponivel");
    }
    printf("\nID: %d | %s\n", r->id, data);
    printf("Modulo: %s | Operacao: %s\n", r->modulo, r->operacao);
    printf("Descricao: %s\n", r->descricao);
}

// Percorre a pilha do mais recente para o mais antigo.
void listarHistorico(const PilhaHistorico *pilha) {
    const Registro *atual = pilha->topo;
    if (atual == NULL) {
        printf("\nO historico esta vazio.\n");
        return;
    }
    while (atual != NULL) {
        mostrarRegistro(atual);
        atual = atual->proximo;
    }
}

// Procura um registro pelo seu ID.
void buscarHistorico(const PilhaHistorico *pilha, int id) {
    const Registro *atual = pilha->topo;
    while (atual != NULL) {
        if (atual->id == id) {
            mostrarRegistro(atual);
            return;
        }
        atual = atual->proximo;
    }
    printf("Registro nao encontrado.\n");
}

// Remove o topo da pilha (uso interno ou teste da estrutura).
int desempilharHistorico(PilhaHistorico *pilha) {
    if (pilha->topo == NULL) return 0;
    Registro *removido = pilha->topo;
    pilha->topo = removido->proximo;
    free(removido);
    return 1;
}

// Libera toda a memoria ao encerrar o programa.
void liberarHistorico(PilhaHistorico *pilha) {
    while (desempilharHistorico(pilha)) { }
}
