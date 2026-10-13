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


int inserirQuartos(Quarto *listaQuarto, int *qtdQuartos, int Numero, TipoQuarto Tipo, int Capacidade, float Diaria);

int removerQuartos(Quarto *listaQuarto, int *qtdQuartos, int Numero);

int buscarQuartoNumero(Quarto *listaQuarto, int qtdQuartos, int Numero);

void listarQuartos(Quarto *listaQuarto, int qtdQuartos, int tipoListagem);

void imprimirDadosQuarto(Quarto *quarto);


#endif













