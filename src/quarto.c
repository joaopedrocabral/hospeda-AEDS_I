#include <stdlib.h>
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
}

const char* statusToString(StatusQuarto status) {
    switch(status) {
        case DISPONIVEL: return "Disponível";
        case RESERVADO:  return "Reservado";
        case OCUPADO:    return "Ocupado";
        default:         return "Desconhecido";
    }
}// Função que transforma os valores dos enums para texto legivel

// Obtém o andar a partir do número do quarto
int obterAndar(int Numero){
    return Numero / 100;
}

//Cria e inicializa um novo quarto
Quarto *criarQuarto(int Numero,TipoQuarto Tipo,int Capacidade,float Diaria,StatusQuarto Status){
    
    Quarto *novo = malloc(sizeof(Quarto));
    
    if(novo == NULL){
        return NULL;
    }
    novo ->Numero = Numero;
    novo ->Andar = obterAndar(Numero);

    novo ->Tipo = Tipo;
    novo ->Capacidade = Capacidade;

    novo ->Diaria = Diaria;

    novo ->Status = Status;

    novo ->esq = NULL;
    novo ->dir = NULL;

    return novo;
}


void imprimirDadosQuarto(Quarto *quarto){
    if(quarto == NULL){
        return;
    }
    printf("Número: %d\n", quarto->Numero);
    printf ("Andar: %d\n",quarto ->Andar);
    printf("Tipo: %s\n", tipoToString(quarto->Tipo));
    printf("Capacidade: %d\n", quarto->Capacidade);
    printf("Diária: R$ %.2f\n", quarto->Diaria);
    printf("Status: %s\n", statusToString(quarto->Status));
}

// Insere um quarto na árvore
Quarto *inserirQuartos(Quarto *raiz,Quarto *novo){
    if (raiz == NULL){
        return novo;
    }

    if (novo ->Numero < raiz->Numero){
        raiz ->esq = inserirQuartos(
            raiz->esq,
            novo
        );
    }else if (novo->Numero > raiz->Numero){
        raiz ->dir = inserirQuartos(
            raiz->dir,
            novo
        );
    }else{
        printf("Já existe um quarto com o número %d.\n",novo->Numero);
        free(novo);
    }
    return raiz;
}

// Encontra o menor quarto da subárvore
Quarto *menorQuarto(Quarto *raiz){
    while (raiz != NULL && raiz ->esq != NULL){
        raiz = raiz ->esq;
    }
    
    return raiz;
}

// Remove um quarto da árvore
Quarto *removerQuartos(Quarto *raiz, int Numero){
    if (raiz == NULL){
        return NULL;
    }
    
    if (Numero < raiz->Numero){
        raiz->esq = removerQuartos(raiz->esq, Numero);
    }else if(Numero > raiz->Numero){
        raiz->dir = removerQuartos(raiz->dir, Numero);
    }else{
        
        /*Quarto com status diferente de disponivel*/
        if (raiz->Status != DISPONIVEL){
            printf("\nNão foi possivel remover Quarto %d.\n",Numero);
            return raiz;
        }

        /*Sem filhos*/
        if (raiz->esq== NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }

        /*Só um filho na direita*/
        if (raiz->esq == NULL){
            Quarto *temp = raiz ->dir;
            free(raiz);
            return temp;
        }
        
        /*Só um filho na esquerda*/
        if (raiz->dir == NULL){
            Quarto *temp = raiz ->esq;
            free(raiz);
            return temp;
        }

        /*Dois filhos*/
        Quarto *temp = menorQuarto(raiz->dir);

        // Copia os dados do sucessor
        raiz->Numero = temp->Numero;
        raiz->Andar = temp->Andar;
        raiz->Tipo = temp->Tipo;
        raiz->Capacidade = temp ->Capacidade;
        raiz->Diaria = temp->Diaria;
        raiz ->Status = temp->Status;

        // Remove o sucessor da árvore
        raiz->dir = removerQuartos(raiz->dir, temp->Numero);
    }

    return raiz;

}

// Busca um quarto pelo número
Quarto *buscarQuartoNumero(Quarto *raiz, int Numero){
    if (raiz==NULL){
        return NULL;
    }

    if (raiz->Numero == Numero){
        return raiz;
    }

    if (Numero < raiz->Numero){
        return buscarQuartoNumero(
            raiz->esq,
            Numero
        );
    }

    if (Numero > raiz->Numero){
        return buscarQuartoNumero(
            raiz->dir,
            Numero
        );
    }

    return NULL;
}

// Lista os quartos em ordem crescente
void listarQuartos(Quarto *raiz){
    if (raiz == NULL){
        return;
    }
    
    //pecorre a subarvore da esquerda
    listarQuartos(raiz->esq);
    
    //quarto atual
    imprimirDadosQuarto(raiz);

    printf("\n=====================\n");

    //pecorre a subarvore da direita
    listarQuartos(raiz->dir);
    
}
