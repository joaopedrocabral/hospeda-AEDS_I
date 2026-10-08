#include <string.h>
#include <ctype.h>
#include "../include/cliente.h"

int validarNome(char nome[]){
    int contemLetras = 0;

    for(int i = 0; nome[i] != '\0'; i++){

        if(isalpha(nome[i])){

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

        if(isdigit(cpf[i])){

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

        if(isdigit(telefone[i])){

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

int inserirCliente(int *qtdClientes, Cliente *listaClientes, int id, char nome[], char cpf[], char telefone[]){
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

    novoCliente.id = id;

    char nomeFormatado[100];
    formatarNome(nome, &nomeFormatado);
    strcpy(novoCliente.nome, nomeFormatado);

    char cpfFormatado[20];
    formatarCpf(cpf, &cpfFormatado);
    strcpy(novoCliente.cpf, cpfFormatado);

    char telefoneFormatado[20];
    formatarTelefone(telefone, &telefoneFormatado);
    strcpy(novoCliente.telefone, telefoneFormatado);

    listaClientes[*qtdClientes] = novoCliente;

    (*qtdClientes)++;

    return 1;
}