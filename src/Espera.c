#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/Espera.h"

void iniciarFila(FilaEspera *fila){
    fila->inicio = NULL;
    fila->fim =NULL;
}

Espera *criarSolicitacao(int IdSolicitacao,int IdCliente, int NumeroQuarto, char DataEntrada[], char DataSaida[]){
    Espera *nova = malloc(sizeof(Espera));

    if (nova == NULL){
        return NULL;
    }

    nova->IdSolicitacao = IdSolicitacao;
    nova->IdCliente = IdCliente;
    nova->NumeroQuarto = NumeroQuarto;
    snprintf(nova->DataEntrada, sizeof(nova->DataEntrada), "%s", DataEntrada);
    snprintf(nova->DataSaida, sizeof(nova->DataSaida), "%s", DataSaida);

    nova->prox= NULL;

    return nova;
}

void enfilerar(FilaEspera *fila, Espera *nova){
    
    if (fila->inicio==NULL){
        fila->inicio = nova;
        fila->fim = nova;
        
        return;
    }
   
    fila->fim->prox = nova;
    fila->fim = nova;
}

Espera *desenfilerar(FilaEspera *fila){
    
    if (fila->inicio==NULL){
        return NULL;
    }
    
    Espera *removida = fila->inicio;

    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL){
        fila->fim = NULL;
    }
    
    removida->prox = NULL;
    
    return removida;
}

Espera *buscarSolicitacao(FilaEspera *fila,int IdSolicitacao){

    Espera *atual = fila->inicio;

    while (atual != NULL){
        if (atual->IdSolicitacao == IdSolicitacao){
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
    
}

void imprimirSolicitacao(Espera *Solicitacao){
    if (Solicitacao == NULL){
        return;
    }
    printf("ID Solicitação: %d\n",Solicitacao->IdSolicitacao);
    printf("ID Cliente: %d\n",Solicitacao->IdCliente);
    printf("Numero do Quarto: %d\n",Solicitacao->NumeroQuarto);
    printf("Data de Entrada: %s\n",Solicitacao->DataEntrada);
    printf("Data de Saida: %s\n",Solicitacao->DataSaida);
}

void listarFila(FilaEspera *fila){
    
    Espera *atual = fila->inicio;

    if (atual==NULL){
        printf("Fila de espera vazia.");
        return;
    }
    
    while (atual != NULL){
        imprimirSolicitacao(atual);
        printf("====================");
        atual= atual->prox;
    }
    
}