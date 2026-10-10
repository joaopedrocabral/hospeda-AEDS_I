#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../include/quarto.h"

#define Max_quartos 100  //define a quantidade maxima de quartos

static int qtdQuartos = 0; //variavel statica que controla a quantidade de quartos cadastrados dentro do arquivo .c

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


int inserirQuartos(Quarto *listaQuarto, int Numero, TipoQuarto Tipo, int Capacidade, float Diaria, StatusQuarto Status){
    if (qtdQuartos >=Max_quartos){
        printf("Lista de quartos com capacidade máxima\n");
    }//Verifica se atingiu a quantidade de quartos maxima
    
    for (int i = 0; i < qtdQuartos; i++){
        if (listaQuarto[i].Numero == Numero){
            printf("Quarto com este numero já está cadastrado\n");
        }
        
    }// Pecorre o vetor que verifica se não tem numero repetido
    
    listaQuarto[qtdQuartos].Numero == Numero;
    listaQuarto[qtdQuartos].Tipo == Tipo;
    listaQuarto[qtdQuartos].Capacide == Capacidade;
    listaQuarto[qtdQuartos].Diaria == Diaria;
    listaQuarto[qtdQuartos].Status == DISPONIVEL; //Adiciona as carecteriscas do quarto e mantem o status inicial como DISPONIVEL

    return 1;
}

int removerQuartos(Quarto *listaQuarto, int Numero, StatusQuarto Status){
    
    for (int i = 0; i < qtdQuartos; i++){
        if (listaQuarto[i].Numero== Numero){
            if (listaQuarto[i].Status != DISPONIVEL){
                printf("Não é possivel remover, o quarto %d nao esta DISPONIVEL.\n", Numero);
            }
        }//Busca o quarto pelo numero e so pode remover quando estiver co o status de disponivel
        
        for (int j = i ; j < qtdQuartos - 1; j++){
            listaQuarto[j] = listaQuarto[j+1];
        }//remove o quarto e desloca o vetor.
        qtdQuartos --;
        return 1;
    }
    printf("Quarto %d não encontrado.\n", Numero);//Retorna um aviso caso o quarto do numero indicado não exista.
    return 0;

}

int buscarQuartoNumero(Quarto *listaQuarto, int Numero){
    for (int i = 0; i < qtdQuartos; i++){
        if (listaQuarto[i].Numero){
            printf("Quarto encontrado: \n");
            
            printf("Número: %d | Tipo: %s | Capacidade: %d | Diária: %.2f | Status: %s\n",listaQuarto[i].Numero,tipoToString(listaQuarto[i].Tipo),listaQuarto[i].Capacide,listaQuarto[i].Diaria, statusToString(listaQuarto[i].Status));
            
            return i;
        }
        printf("Quarto %d não encontrado.\n", Numero);
        return -1;
    }
}//Busca o quarto imprime as suas informações e caso não tenha um quarto referente ao numero irá retornar uma mensagem de aviso.

void listarQuarto(Quarto *listaQuarto, StatusQuarto Status){
    for (int i = 0; i < qtdQuartos; i++){
        if (Status == listaQuarto[i].Status || Status == -1){
            printf("Número: %d | Tipo: %s | Capacidade: %d | Diária: %.2f | Status: %s\n",listaQuarto[i].Numero,tipoToString(listaQuarto[i].Tipo),listaQuarto[i].Capacide,listaQuarto[i].Diaria, statusToString(listaQuarto[i].Status));
        }
        
    }

}// Lista todos os quartos ou pelo seu status.

