#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/cliente.h"
#include "../include/reserva.h"
#include "../include/quarto.h"

int converterData(char data[], time_t *dataConvertida) {
    int dia, mes, ano;

    if (strlen(data) != 10) {
        return 0;
    }

    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (mes < 1 || mes > 12 || dia < 1 || ano < 1900) {
        return 0;
    }

    struct tm dataTM = {0};

    dataTM.tm_mday = dia;
    dataTM.tm_mon = mes - 1;
    dataTM.tm_year = ano - 1900;
    dataTM.tm_hour = 12;

    time_t resultado = mktime(&dataTM);

    if (resultado == (time_t)-1 ||
        dataTM.tm_mday != dia ||
        dataTM.tm_mon != mes - 1 ||
        dataTM.tm_year != ano - 1900) {
        return 0;
    }

    *dataConvertida = resultado;

    return 1;
}

int validarDatasReserva(char dataCheckIn[], char dataCheckOutPrevista[]) {
    time_t checkIn, checkOut;

    if (converterData(dataCheckIn, &checkIn) == 0 || converterData(dataCheckOutPrevista, &checkOut) == 0) {
        return 0;
    }

    return difftime(checkOut, checkIn) > 0;
}

float calcularValorReserva(float valorDiaria, char dataCheckIn[], char dataCheckOutPrevista[]) {
    time_t checkIn, checkOut;

    if (converterData(dataCheckIn, &checkIn) == 0 || converterData(dataCheckOutPrevista, &checkOut) == 0) {
        return -1.0;
    }

    int qtdNoites = difftime(checkOut, checkIn) / 86400;

    return qtdNoites * valorDiaria;
}

int inicializarListaReservas(ListaReservas *listaReservas){
    if (listaReservas == NULL) {
        return 0;
    }

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

void imprimirDadosReserva(Reserva *reserva, ListaClientes *listaClientes){

    NoCliente *cliente = NULL;

    if (listaClientes != NULL) {
        cliente = buscarClienteId(listaClientes, reserva->idCliente);
    }

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

void listarReservasCliente(ListaReservas *listaReservas, ListaClientes *listaClientes, int idCliente) {
    NoReserva *atual = listaReservas->primeiro->proximo;

    while (atual != NULL) {
        if (atual->dados.idCliente == idCliente) {
            imprimirDadosReserva(&atual->dados, listaClientes);
        }

        atual = atual->proximo;
    }
}

int verificarDisponibilidadeQuarto(ListaReservas *listaReservas, int numeroQuarto, char dataCheckIn[], char dataCheckOutPrevista[]){
    time_t inicioSolicitado;
    time_t fimSolicitado;

    if (converterData(dataCheckIn, &inicioSolicitado) == 0 || converterData(dataCheckOutPrevista, &fimSolicitado) == 0){
        return 0;
    }

    NoReserva *atual = listaReservas->primeiro->proximo;

    while (atual != NULL) {
        Reserva *reserva = &atual->dados;

        if (reserva->numeroQuarto == numeroQuarto && (reserva->status == AGENDADA || reserva->status == EM_ANDAMENTO)){

            time_t inicioExistente, fimExistente;

            converterData(reserva->dataCheckIn, &inicioExistente);
            converterData(reserva->dataCheckOutPrevista, &fimExistente);

            if (difftime(inicioSolicitado, fimExistente) < 0 && difftime(inicioExistente, fimSolicitado) < 0){
                return 0;
            }
        }
        atual = atual->proximo;
    }

    return 1;
}

float calcularMulta(float valorDiaria, char dataCheckOutPrevista[], char dataCheckOutEfetiva[]){
    time_t prevista;
    time_t efetiva;

    if (converterData(dataCheckOutPrevista, &prevista) == 0 || converterData(dataCheckOutEfetiva, &efetiva) == 0) {
        return -1.0;
    }

    if (difftime(efetiva, prevista) <= 0) {
        return 0.0;
    }

    int diasAtraso = difftime(efetiva, prevista) / 86400;

    return diasAtraso * valorDiaria;
}

int criarReserva(ListaReservas *listaReservas, ListaClientes *listaClientes, Quarto *arvoreQuartos, int idReserva, int idCliente, int numeroQuarto, char dataCheckIn[], char dataCheckOutPrevista[]){
    
    if (listaReservas == NULL || listaClientes == NULL || arvoreQuartos == NULL){
        printf("Erro ao acessar os dados do sistema.\n");
        return 0;
    }

    if (buscarClienteId(listaClientes, idCliente) == NULL){
        printf("Cliente não encontrado.\n");
        return 0;
    }

    Quarto *quarto = buscarQuartoNumero(arvoreQuartos, numeroQuarto);

    if (quarto == NULL) {
        printf("Quarto não encontrado.\n");
        return 0;
    }

    if (quarto->Diaria <= 0) {
        printf("Valor da diária inválido.\n");
        return 0;
    }

    if (validarDatasReserva(dataCheckIn, dataCheckOutPrevista) == 0){
        printf("Período da reserva inválido.\n");
        return 0;
    }

    if (verificarDisponibilidadeQuarto(listaReservas, numeroQuarto, dataCheckIn, dataCheckOutPrevista) == 0){
        printf("Quarto indisponível para o período informado.\n");
        return 0;
    }

    float valorTotal = calcularValorReserva(quarto->Diaria, dataCheckIn, dataCheckOutPrevista);

    NoReserva *atual = listaReservas->primeiro->proximo;

    Reserva reserva = {0};

    reserva.id = idReserva;
    reserva.idCliente = idCliente;
    reserva.numeroQuarto = numeroQuarto;
    strcpy(reserva.dataCheckIn, dataCheckIn);
    strcpy(reserva.dataCheckOutPrevista, dataCheckOutPrevista);
    reserva.valorTotal = valorTotal;
    reserva.multa = 0;
    reserva.status = AGENDADA;

    if (inserirReserva(listaReservas, reserva) == 0) {
        return 0;
    }

    printf("Reserva criada com sucesso. ID: %d\n", idReserva);

    return 1;
}

int cancelarReserva(ListaReservas *listaReservas, int idReserva){

    NoReserva *novoNo = buscarReservaId(listaReservas, idReserva);

    if (novoNo == NULL || novoNo->dados.status != AGENDADA) {
        printf("Não foi possível cancelar a reserva.\n");
        return 0;
    }
    novoNo->dados.status = CANCELADA;
    return 1;
}

int realizarCheckIn(ListaReservas *listaReservas, int idReserva){
    NoReserva *novoNo = buscarReservaId(listaReservas, idReserva);

    if (novoNo == NULL || novoNo->dados.status != AGENDADA) {
        printf("Não foi possível realizar o check-in. A reserva não está com o status AGENDADA.\n");
        return 0;
    }
    novoNo->dados.status = EM_ANDAMENTO;
    return 1;
}

int realizarCheckOut(ListaReservas *listaReservas, int idReserva, char dataCheckOutEfetiva[], Quarto *arvoreQuartos) {
    NoReserva *novoNo = buscarReservaId(listaReservas, idReserva);

    if (novoNo == NULL || novoNo->dados.status != EM_ANDAMENTO) {
        printf("Não foi possível realizar o check-out.\n");
        return 0;
    }

    if (arvoreQuartos == NULL) {
        return 0;
    }

    if (validarDatasReserva(novoNo->dados.dataCheckIn, dataCheckOutEfetiva) == 0) {
        printf("Data de check-out efetiva inválida.\n");
        return 0;
    }

    Quarto *quarto = buscarQuartoNumero(arvoreQuartos, novoNo->dados.numeroQuarto);

    if (quarto == NULL) {
        printf("Quarto não encontrado.\n");
        return 0;
    }

    float multa = calcularMulta(quarto->Diaria, novoNo->dados.dataCheckOutPrevista, dataCheckOutEfetiva);

    if (multa < 0) {
        printf("Não foi possível calcular a multa.\n");
        return 0;
    }

    strcpy(novoNo->dados.dataCheckOutEfetiva, dataCheckOutEfetiva);

    novoNo->dados.multa = multa;
    novoNo->dados.status = FINALIZADA;

    return 1;
}
