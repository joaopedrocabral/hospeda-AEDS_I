#include <time.h>
#include "../include/cliente.h"
#include "../include/quarto.h"

typedef enum {
    AGENDADA,
    EM_ANDAMENTO,
    FINALIZADA,
    CANCELADA
} StatusReserva;

typedef struct {
    int id;
    int idCliente;
    int numeroQuarto;

    char dataCheckIn[11];
    char dataCheckOutPrevista[11];
    char dataCheckOutEfetiva[11];

    float valorTotal;
    float multa;

    StatusReserva status;
} Reserva;

typedef struct NoReserva {
    Reserva dados;
    struct NoReserva *proximo;
} NoReserva;

typedef struct {
    NoReserva *primeiro;
    NoReserva *ultimo;
} ListaReservas;

int inicializarListaReservas(ListaReservas *listaReservas);

//Responsável pela criação da reserva e regras de negócio
int criarReserva(
    ListaReservas *listaReservas,
    ListaClientes *listaClientes,
    ArvoreQuartos *arvoreQuartos,
    int codigo,
    int idCliente,
    int numeroQuarto,
    char dataCheckIn[],
    char dataCheckOutPrevista[]
);

//Responsável pela inserção da reserva na lista de reservas
int inserirReserva(ListaReservas *listaReservas, Reserva reserva);

NoReserva *buscarReservaId(ListaReservas *listaReservas, int idReserva);

void listarReservas(ListaReservas *listaReservas, ListaClientes *listaClientes);

void listarReservasCliente(ListaReservas *listaReservas, int idCliente);

int validarDatasReserva(char dataCheckIn[], char dataCheckOutPrevista[]);

int verificarDisponibilidadeQuarto(
    ListaReservas *listaReservas,
    int numeroQuarto,
    char dataCheckIn[],
    char dataCheckOutPrevista[]
);

int cancelarReserva(ListaReservas *listaReservas, int idReserva);

int realizarCheckIn(ListaReservas *listaReservas, int idReserva, ArvoreQuartos *arvoreQuartos);

int realizarCheckOut(
    ListaReservas *listaReservas,
    int idReserva,
    char dataCheckOutEfetiva[],
    ArvoreQuartos *arvoreQuartos
);

float calcularValorReserva(
    float valorDiaria,
    char dataCheckIn[],
    char dataCheckOutPrevista[]
);

float calcularMulta(
    float valorDiaria,
    char dataCheckOutPrevista[],
    char dataCheckOutEfetiva[]
);

int converterData(char data[], time_t *dataConvertida);

