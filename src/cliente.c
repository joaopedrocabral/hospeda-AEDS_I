#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../include/cliente.h"

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

void imprimirDados(Cliente *cliente){
    printf("ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);

    printf("CPF: %.3s.%.3s.%.3s-%.2s\n", cliente->cpf, cliente->cpf+3, cliente->cpf+6, cliente->cpf+9);

    if(strlen(cliente->telefone) == 11){
        printf("Telefone: (%.2s) %.5s-%.4s\n", cliente->telefone, cliente->telefone+2, cliente->telefone+7);

    } else {
        printf("Telefone: (%.2s) %.4s-%.4s\n", cliente->telefone, cliente->telefone+2, cliente->telefone+6);
    }

}

int inserirCliente(Cliente *listaClientes, int *qtdClientes, int idCliente, char nome[], char cpf[], char telefone[]){
    Cliente novoCliente;

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

    novoCliente.id = idCliente;

    char nomeFormatado[100];
    formatarNome(nome, nomeFormatado);
    strcpy(novoCliente.nome, nomeFormatado);

    char cpfFormatado[20];
    formatarCpf(cpf, cpfFormatado);
    strcpy(novoCliente.cpf, cpfFormatado);

    char telefoneFormatado[20];
    formatarTelefone(telefone, telefoneFormatado);
    strcpy(novoCliente.telefone, telefoneFormatado);

    listaClientes[*qtdClientes] = novoCliente;

    (*qtdClientes)++;

    return 1;
}

int removerCliente(Cliente *listaClientes, int *qtdClientes, int idCliente){

    int indiceCliente = buscarClienteId(listaClientes, *qtdClientes, idCliente);

    if(indiceCliente == -1){
        return 0;
    }

    for(int i = indiceCliente; i < *qtdClientes - 1; i++){

        listaClientes[i] = listaClientes[i + 1];
    }

    (*qtdClientes)--;

    return 1;
}

int buscarClienteId(Cliente *listaClientes, int qtdClientes, int idCliente){
    
    for(int i = 0; i < qtdClientes; i++){
        
        if(listaClientes[i].id == idCliente){
            return i;
        }
    }

    printf("ERRO! Cliente não encontrado!\n");

    return -1;
};

int buscarClienteCpf(Cliente *listaClientes, int qtdClientes, char cpf[]){
    
    for(int i = 0; i < qtdClientes; i++){
        
        if((strcmp(listaClientes[i].cpf, cpf)) == 0){
            return i;
        }
    }

    printf("ERRO! Cliente não encontrado!\n");
    return -1;
};

int buscarClienteNome(Cliente *listaClientes, int qtdClientes, char nome[]){
    
    for(int i = 0; i < qtdClientes; i++){
        
        if((strcmp(listaClientes[i].nome, nome)) == 0){
            return i;
        }
    }

    printf("ERRO! Cliente não encontrado!\n");

    return -1;
};

void listarClientes(Cliente *listaClientes, int qtdClientes){

    for(int i = 0; i < qtdClientes; i++){

        imprimirDados(&listaClientes[i]);

        printf("\n-------------------------------\n");
    }
}