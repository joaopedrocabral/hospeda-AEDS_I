#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/cliente.h"
#include "../include/reserva.h"

int validarNome(char nome[]){
    int contemLetras = 0;

    for(int i = 0; nome[i] != '\0'; i++){

        if(isalpha((unsigned char)nome[i])){

            contemLetras = 1;
        
        }
    }

    return contemLetras;

}

void formatarNome(char nome[], char *nomeFormatado){
    int inicioNome = 0;
    int fimNome = strlen(nome) - 1;

    while (nome[inicioNome] == ' '){
        inicioNome++;
    }

    while (nome[fimNome] == ' '){
        fimNome--;
    }

    int j = 0;

    for(int i = inicioNome; i <= fimNome; i++){
        nomeFormatado[j] = nome[i];
        j++;
    }

    nomeFormatado[j] = '\0';
}

int validarCpf(char cpf[]){
    int qtdDigitos = 0;

    for(int i = 0; cpf[i] != '\0'; i++){

        if(isdigit((unsigned char)cpf[i])){

            qtdDigitos++;

        } else if(cpf[i] != ' '){
            
            return 0;
        }

        
    }

    return (qtdDigitos == 11) ? 1 : 0;
}

void formatarCpf(char cpf[], char *cpfFormatado){
    int j = 0;

    for(int i = 0; cpf[i] != '\0'; i++){

        if(isdigit(cpf[i])){
            cpfFormatado[j] = cpf[i];
            j++;

        }
    }

    cpfFormatado[j] = '\0';
}

int validarTelefone(char telefone[]){
    int qtdDigitos = 0;

    for(int i = 0; telefone[i] != '\0'; i++){

        if(isdigit((unsigned char)telefone[i])){

            qtdDigitos++;

        } else if(telefone[i] != ' '){
            
            return 0;

        }

    }

    return (qtdDigitos == 11 || qtdDigitos == 10) ? 1 : 0;
}

void formatarTelefone(char telefone[], char *telefoneFormatado){
    int j = 0;

    for(int i = 0; telefone[i] != '\0'; i++){

        if(isdigit(telefone[i])){
            telefoneFormatado[j] = telefone[i];
            j++;
        }
    }

    telefoneFormatado[j] = '\0';
}

void imprimirDadosCliente(Cliente *cliente){
    printf("ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);

    printf("CPF: %.3s.%.3s.%.3s-%.2s\n", cliente->cpf, cliente->cpf+3, cliente->cpf+6, cliente->cpf+9);

    if(strlen(cliente->telefone) == 11){
        printf("Telefone: (%.2s) %.5s-%.4s\n", cliente->telefone, cliente->telefone+2, cliente->telefone+7);

    } else {
        printf("Telefone: (%.2s) %.4s-%.4s\n", cliente->telefone, cliente->telefone+2, cliente->telefone+6);
    }

}

int inicializarListaClientes(ListaClientes *listaClientes){
    NoCliente *novoNo = malloc(sizeof(NoCliente));

    if(novoNo == NULL){
        printf("Erro ao alocar memória para Clientes.\n");
        return 0;
    }

    novoNo->proximo = NULL;

    listaClientes->primeiro = novoNo;
    listaClientes->ultimo = novoNo;

    return 1;
}

int inserirCliente(ListaClientes *listaClientes, int *qtdClientes, int idCliente, char nome[], char cpf[], char telefone[]){
    
    if(!validarNome(nome)){

        printf("ERRO! O nome digitado é inválido!\n");
        return 0;

    }
    
    if(!validarCpf(cpf)){

        printf("ERRO! O CPF digitado é inválido!\n");
        return 0;

    }

    if(!validarTelefone(telefone)){
        
        printf("ERRO! O Telefone digitado é inválido!\n");
        return 0;

    }

    char cpfFormatado[20];
    formatarCpf(cpf, cpfFormatado);

    if((buscarClienteCpf(listaClientes, cpfFormatado)) != NULL){
        printf("Já existe um cliente com esse CPF.");
        return 0;
    };

    NoCliente *novoNo = malloc(sizeof(NoCliente));

    if(novoNo == NULL){
        printf("Erro ao alocar memória.\n");
        return 0;
    }

    novoNo->dados.id = idCliente;

    strcpy(novoNo->dados.cpf, cpfFormatado);

    char nomeFormatado[100];
    formatarNome(nome, nomeFormatado);
    strcpy(novoNo->dados.nome, nomeFormatado);

    char telefoneFormatado[20];
    formatarTelefone(telefone, telefoneFormatado);
    strcpy(novoNo->dados.telefone, telefoneFormatado);

    novoNo->proximo = NULL;

    listaClientes->ultimo->proximo = novoNo;

    listaClientes->ultimo = novoNo;

    (*qtdClientes)++;

    return 1;
}

int removerCliente(ListaClientes *listaClientes, int *qtdClientes, int idCliente){

    NoCliente *anterior = listaClientes->primeiro;
    NoCliente *atual = anterior->proximo;

    while(atual != NULL && atual->dados.id != idCliente){
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("Cliente não encontrado!\n");
        return 0;
    }

    anterior->proximo = atual->proximo;

    if(atual == listaClientes->ultimo){
        listaClientes->ultimo = anterior;
    }

    free(atual);

    (*qtdClientes)--;

    return 1;
}

NoCliente *buscarClienteId(ListaClientes *listaClientes, int idCliente){
    
    NoCliente *atual = listaClientes->primeiro->proximo;

    while(atual != NULL){
        if(atual->dados.id == idCliente){
            return atual;
        }
        
        atual = atual->proximo;
    }

    return NULL;
};

NoCliente *buscarClienteCpf(ListaClientes *listaClientes, char cpf[]){
    
    NoCliente *atual = listaClientes->primeiro->proximo;

    while (atual != NULL){
        if(strcmp(atual->dados.cpf, cpf) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
};

NoCliente *buscarClienteNome(ListaClientes *listaClientes, char nome[]){
    
   NoCliente *atual = listaClientes->primeiro->proximo;

   while(atual != NULL){
        if(strcmp(atual->dados.nome, nome) == 0){
            return atual;
        }

        atual = atual->proximo;
   }

    return NULL;
};