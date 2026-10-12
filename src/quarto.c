#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../include/quarto.h"

const char* tipoToString(TipoQuarto tipo) {
    switch(tipo) {
        case STANDARD: return "Standard";
        case DELUXE:   return "Deluxe";
        case PREMIUM:  return "Premium";
        default:       return "Desconhecido";
    }
} // Função que transforma os valores dos enums para texto legivel

const char* statusToString(StatusQuarto status) {
    switch(status) {
        case DISPONIVEL: return "Disponível";
        case RESERVADO:  return "Reservado";
        case OCUPADO:    return "Ocupado";
        default:         return "Desconhecido";
    }
}// Função que transforma os valores dos enums para texto legivel

void imprimirDadosQuarto(Quarto *quarto){
    printf("Número: %d\n", quarto->Numero);
    printf("Tipo: %s\n", tipoToString(quarto->Tipo));
    printf("Capacidade: %d\n", quarto->Capacide);
    printf("Diária: R$ %.2f\n", quarto->Diaria);
    printf("Status: %s\n", statusToString(quarto->Status));
}

int inserirQuartos(Quarto *listaQuarto, int *qtdQuartos, int Numero, TipoQuarto Tipo, int Capacidade, float Diaria){
    
    if((buscarQuartoNumero(listaQuarto, *qtdQuartos, Numero) != -1)){
        printf("Já existe um quarto com esse número.");
        return 0;
    }// Verifica se já não existe um quarto com esse número
    
    listaQuarto[*qtdQuartos].Numero = Numero;
    listaQuarto[*qtdQuartos].Tipo = Tipo;
    listaQuarto[*qtdQuartos].Capacide = Capacidade;
    listaQuarto[*qtdQuartos].Diaria = Diaria;
    listaQuarto[*qtdQuartos].Status = DISPONIVEL; //Adiciona as carecteriscas do quarto e mantem o status inicial como DISPONIVEL

    (*qtdQuartos)++;

    return 1;
}

int removerQuartos(Quarto *listaQuarto, int *qtdQuartos, int Numero){
    
    //Utiliza a própria função buscar quarto para localizae o índice do quarto no vetor.
    int indiceQuarto = buscarQuartoNumero(listaQuarto, *qtdQuartos, Numero);

    //Realiza verifições se existe o quarto no vetor e se o quarto está com o status DISPONIVEL.
    if(indiceQuarto == -1){
        printf("Quarto não encontrado.");
        return 0;
    }

    if(listaQuarto[indiceQuarto].Status != DISPONIVEL){
        printf("Não é possível remover o quarto Nº %d, pois ele não está DISPONÍVEL.\n", Numero);
        return 0;
    }

    for (int i = indiceQuarto; i < *qtdQuartos - 1; i++){

        listaQuarto[i] = listaQuarto[i+1];

    }
    
    (*qtdQuartos)--;

    return 1;
}

int buscarQuartoNumero(Quarto *listaQuarto, int qtdQuartos, int Numero){
    
    for(int i = 0; i < qtdQuartos; i++){
        
        if(listaQuarto[i].Numero == Numero){
            return i;
        }
    }

    return -1;
};

void listarQuartos(Quarto *listaQuarto, int qtdQuartos, int tipoListagem){
    /*
    tipoListagem = 0 -> Listagem Completa
    tipoListagem = 1 -> Listagem dos Disponíveis
    */

    if(tipoListagem == 0){

        for(int i = 0; i < qtdQuartos; i++){

            imprimirDadosQuarto(&listaQuarto[i]);

            printf("\n-------------------------------\n");
        }

    } else if(tipoListagem == 1){

        int quartosDisponiveis = 0;

        for(int i = 0; i < qtdQuartos; i++){

            if(listaQuarto[i].Status == DISPONIVEL){
                imprimirDadosQuarto(&listaQuarto[i]);

                printf("\n-------------------------------\n");

                quartosDisponiveis++;
            }

        }

        if(quartosDisponiveis == 0){
            printf("Não há quartos diponíveis nesse momento.\n");
        }

    } else {
        printf("Tipo de Listagem selecionada é inválida.\n");
    }

}// Lista todos os quartos ou pelo seu status.
