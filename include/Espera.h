#ifndef ESPERA_H
#define ESPERA_H

typedef struct Espera{
    int IdSolicitacao;
    int IdCliente;
    int NumeroQuarto;
    char DataEntrada[11];
    char DataSaida[11];
    struct Espera *prox;

}Espera;

typedef struct{
    Espera *inicio;
    Espera *fim;
}FilaEspera;

void iniciarFila(FilaEspera *fila); //inicia a fila

Espera *criarSolicitacao(int IdSolicitacao,int IdCliente, int NumeroQuarto, char DataEntrada[], char DataSaida[]); // cria uma nova solicitação

void *enfilerar(FilaEspera *fila, Espera *nova); //Adiciona no final da fila

Espera *desenfilerar(FilaEspera *fila); //Remove o primeiro da fila

Espera *buscarSolicitacao(FilaEspera *fila,int IdSolicitacao); //Busca a solicitação pelo ID

void listarFila(FilaEspera *fila); //lista toda a fila

void imprimirSolicitacao(Espera *Solicitacao); //exibe uma solicitação

#endif
