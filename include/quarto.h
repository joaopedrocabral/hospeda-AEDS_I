#ifndef QUARTO_H
#define QUARTO_H


typedef enum {
    STANDARD,
    DELUXE,
    PREMIUM
}TipoQuarto;

typedef enum {
    DISPONIVEL,
    RESERVADO,
    OCUPADO
}StatusQuarto;

typedef struct {
    int Numero;
    TipoQuarto Tipo;
    int Capacide;
    float Diaria;
    StatusQuarto Status;
}Quarto;


int inserirQuartos(Quarto *listaQuarto, int Numero, TipoQuarto Tipo, int Capacidade, float Diaria, StatusQuarto Status);

int removerQuartos(Quarto *listaQuarto, int Numero, StatusQuarto Status);

int buscarQuartoNumero(Quarto *listaQuarto, int Numero);

void listarQuarto(Quarto *listaQuarto, StatusQuarto Status);


#endif













