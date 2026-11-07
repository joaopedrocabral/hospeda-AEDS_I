#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../include/reserva.h"

int converterData(char data[], time_t *dataConvertida){
    int dia, mes, ano;

    if(sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3){
        return 0;
    }

    if(mes < 1 || mes > 12 || dia < 1 || ano < 1900) {
        return 0;
    }

    struct tm dataTM = {0};

    dataTM.tm_mday = dia;
    dataTM.tm_mon = mes - 1;
    dataTM.tm_year = ano - 1900;
    dataTM.tm_hour = 12;

    time_t resultado = mktime(&dataTM);

    if(resultado == (time_t)-1){
        return 0;
    }

    if(dataTM.tm_mday != dia || dataTM.tm_mon != mes - 1 || dataTM.tm_year != ano - 1900) {
        return 0;
    }

    *dataConvertida = resultado;

    return 1;
}

int validarDatasReserva(char dataCheckIn[], char dataCheckOutPrevista[]){
    time_t checkIn;
    time_t checkOut;

    if(converterData(dataCheckIn, &checkIn) == 0){
        return 0;
    }

    if (!converterData(dataCheckOutPrevista, &checkOut)) {
        return 0;
    }

    return difftime(checkOut, checkIn) > 0;
}

float calcularValorReserva(float valorDiaria, char dataCheckIn[], char dataCheckOutPrevista[]){
    time_t checkIn;
    time_t checkOut;

    if(converterData(dataCheckIn, &checkIn) == 0 || converterData(dataCheckOutPrevista, &checkOut) == 0){
        return -1.0f;
    }

    int qtdNoites = (int)(difftime(checkOut, checkIn) / 86400);

    return qtdNoites * valorDiaria;
}

int inicializarListaReservas(ListaReservas *listaReservas){
    NoReserva *novoNo = malloc(sizeof(NoReserva));

    if(novoNo == NULL){
        printf("Erro ao alocar memória para Reservas.\n");
        return 0;
    }

    novoNo->proximo = NULL;

    listaReservas->primeiro = novoNo;
    listaReservas->ultimo = novoNo;

    return 1;
}

int inserirReserva(ListaReservas *listaReservas, Reserva reserva) {
    NoReserva *novoNo = malloc(sizeof(NoReserva));

    if(novoNo == NULL){
        printf("Erro ao alocar memória para Reservas.\n");
        return 0;
    }

    novoNo->dados = reserva;
    novoNo->proximo = NULL;

    listaReservas->ultimo->proximo = novoNo;
    listaReservas->ultimo = novoNo;

    return 1;
}

NoReserva *buscarReservaId(ListaReservas *listaReservas, int idReserva){
    NoReserva *atual = listaReservas->primeiro->proximo;

    while(atual != NULL){
        if(atual->dados.id == idReserva){
            return atual;
        }
        
        atual = atual->proximo;
    }

    return NULL;
}

void imprimirDadosReserva(Reserva *reserva, ListaClientes *listaClientes) {
    NoCliente *cliente = buscarClienteId(listaClientes, reserva->idCliente);

    printf("ID da reserva: %d\n", reserva->id);
    printf("Cliente: %s\n", cliente != NULL ? cliente->dados.nome : "Cliente não encontrado");
    printf("Quarto: %d\n", reserva->numeroQuarto);
    printf("Check-in: %s\n", reserva->dataCheckIn);
    printf("Check-out previsto: %s\n", reserva->dataCheckOutPrevista);

    printf("Check-out efetivo:   %s\n", reserva->dataCheckOutEfetiva[0] != '\0' ? reserva->dataCheckOutEfetiva: "--");

    printf("Valor total: R$ %.2f\n", reserva->valorTotal);
    printf("Multa: R$ %.2f\n", reserva->multa);

    printf("Status:");

    switch (reserva->status) {
        case AGENDADA:
            printf("Agendada\n");
            break;

        case EM_ANDAMENTO:
            printf("Em andamento\n");
            break;

        case FINALIZADA:
            printf("Finalizada\n");
            break;

        case CANCELADA:
            printf("Cancelada\n");
            break;

        default:
            printf("Desconhecido\n");
    }

    printf("----------------------------------------\n");
}

void listarReservas(ListaReservas *listaReservas, ListaClientes *listaClientes){
    NoReserva *atual = listaReservas->primeiro->proximo;

    while(atual != NULL){
        imprimirDadosReserva(&atual->dados, listaClientes);
        atual = atual->proximo;
    }
}
