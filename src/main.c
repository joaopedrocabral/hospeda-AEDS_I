#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cliente.h"
#include "../include/quarto.h"

void limparTela(void){ //Função responsável por limpar a tela do terminal. Identifica se o sistema é Windows ou Linux/macOS
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void lerTexto(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Apenas descarta os caracteres restantes. */
    }
}

int disponibilidadeClientes(Cliente **clientes, int qtdClientes, int *capacidadeClientes){

    if(qtdClientes >= *capacidadeClientes){
        int capacidadeTemp = *capacidadeClientes * 2;

        Cliente *listaTemp = realloc(*clientes, capacidadeTemp * sizeof(Cliente));

        if(listaTemp == NULL){
            printf("Houve um erro ao alocar memória para Clientes.\n");
            return 0;
        }

        *capacidadeClientes *= 2;

        *clientes = listaTemp;

        return 1;
    }

    return 1;
}

int disponibilidadeQuartos(Quarto **quartos, int qtdQuartos, int *capacidadeQuartos){

    if(qtdQuartos >= *capacidadeQuartos){
        int capacidadeTemp = *capacidadeQuartos * 2;

        Quarto *listaTemp = realloc(*quartos, capacidadeTemp * sizeof(Quarto));

        if(listaTemp == NULL){
            printf("Houve um erro ao alocar memória para Quartos.\n");
            return 0;
        }

        *capacidadeQuartos *= 2;

        *quartos = listaTemp;

        return 1;
    }

    return 1;
}

void submenuBuscarClientes(Cliente *clientes, int qtdClientes){
    int opcao;

    do {
        printf("\n===== BUSCAR CLIENTE =====\n");
        printf("1 - Buscar por ID\n");
        printf("2 - Buscar por Nome\n");
        printf("3 - Buscar por CPF\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opção: ");

        scanf("%d", &opcao);
        limparEntrada();

        switch (opcao) {
            case 1: {
                int idCliente;

                printf("\nDigite o ID do cliente: ");
                scanf("%d", &idCliente);
                limparEntrada();

                int indiceCliente = buscarClienteId(clientes, qtdClientes, idCliente);

                limparTela();

                if(indiceCliente == -1){
                    printf("Cliente não encontrado.\n");
                    break;
                }

                printf("\nCliente localizado:\n\n");
                imprimirDadosCliente(&clientes[indiceCliente]);

                break;
            }

            case 2: {
                char nome[100];

                printf("\nNome completo: ");
                lerTexto(nome, sizeof(nome));

                int indiceCliente = buscarClienteNome(clientes, qtdClientes, nome);

                limparTela();

                if(indiceCliente == -1){
                    printf("Cliente não encontrado!\n");
                    break;
                }

                printf("\nCliente localizado:\n\n");
                imprimirDadosCliente(&clientes[indiceCliente]);

                break;
            }

            case 3: {
                char cpf[20];

                printf("\nCPF (somente números): ");
                lerTexto(cpf, sizeof(cpf));

                int indiceCliente = buscarClienteCpf(clientes, qtdClientes, cpf);

                limparTela();

                if(indiceCliente == -1){
                    printf("Cliente não encontrado!\n");
                    break;
                }

                printf("\nCliente localizado:\n\n");
                imprimirDadosCliente(&clientes[indiceCliente]);

                break;
            }

            case 0: {
                limparTela();
                break;
            }

            default: {
                limparTela();
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
        
    } while (opcao != 0);
}

void menuClientes(Cliente **clientes, int *qtdClientes, int *capacidadeClientes, int *proximoIdCliente) {
    int opcao;
    char nome[100];
    char cpf[20];
    char telefone[20];

    do {
        printf("\n========== MENU DE CLIENTES ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Buscar cliente\n");
        printf("3 - Listar clientes\n");
        printf("4 - Remover cliente\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);
        limparEntrada();

        switch (opcao) {
            case 1: {

                if(!(disponibilidadeClientes(clientes, *qtdClientes, capacidadeClientes))){
                    printf("Não é possível cadastrar novos clientes.\n");
                    break;
                }

                printf("\nNome completo: ");
                lerTexto(nome, sizeof(nome));

                printf("CPF (somente números): ");
                lerTexto(cpf, sizeof(cpf));

                printf("Telefone (somente números): ");
                lerTexto(telefone, sizeof(telefone));

                limparTela();

                if (inserirCliente(*clientes, qtdClientes, *proximoIdCliente, nome, cpf, telefone)) {
                    printf("\nCliente cadastrado com sucesso.\n");
                    (*proximoIdCliente)++;

                } else {
                    printf("\nNão foi possivel cadastrar o cliente.\n");
                    break;
                }

                break;
            }

            case 2: {
                limparTela();

                if(*qtdClientes == 0){
                    printf("Nenhum cliente cadastrado.\n");

                } else {
                    submenuBuscarClientes(*clientes, *qtdClientes);
                }
                break;
            }

            case 3: {
                limparTela();

                if (*qtdClientes == 0) {
                    printf("Nenhum cliente cadastrado.\n");

                } else {
                    printf("Clientes Cadastrados: %d \n\n", *qtdClientes);
                    listarClientes(*clientes, *qtdClientes);
                }
                break;
            }

            case 4: {
                if(*qtdClientes == 0){
                    limparTela();
                    printf("Nenhum cliente cadastrado.\n");
                    break;
                }

                int idCliente;

                printf("ID do cliente que deseja remover: ");
                scanf("%d", &idCliente);
                limparEntrada();

                int indiceCliente = buscarClienteId(*clientes, *qtdClientes, idCliente);

                limparTela();

                if(indiceCliente == -1){
                    printf("Cliente não encontrado.\n");
                    break;
                }

                printf("\nDeseja realmente remover o cliente %d - %s?\n", idCliente, (*clientes)[indiceCliente].nome);

                int opcao;

                do {
                    printf("\n1 - Confirmar\n");
                    printf("2 - Cancelar\n");
                    printf("\nEscolha uma opção: ");

                    scanf("%d", &opcao);
                    limparEntrada();

                    limparTela();

                    switch (opcao){
                        case 1:
                            if(removerCliente(*clientes, qtdClientes, idCliente)) {
                            printf("Cliente removido com sucesso.\n");
                            }
                        break;

                        case 2:
                            printf("Operação cancelada. Retornando ao menu clientes.\n");
                        break;

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }        


                } while (opcao != 1 && opcao != 2);

                break;
            } 

            case 0:
                limparTela();
                printf("Voltando ao menu principal...\n");
            break;


            default:
                limparTela();
                printf("Opcao inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

int submenuTipoQuarto(TipoQuarto *tipoQuarto) {
    int opcao;

    do {
        printf("Tipo do quarto:\n");
        printf("1 - Standard\n");
        printf("2 - Deluxe\n");
        printf("3 - Premium\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opção: ");

        scanf("%d", &opcao);
        limparEntrada();

        switch(opcao){
            case 1:
                *tipoQuarto = STANDARD;
            return 1;
            
            case 2:
                *tipoQuarto = DELUXE;
            return 1;

            case 3:
                *tipoQuarto = PREMIUM;
            return 1;

            case 0:
                return 0;
            break;

            default:
                printf("Opção inválida, tente novamente.\n");

        }
    } while (opcao != 0);

    return 1;
}

void menuQuartos(Quarto **quartos, int *qtdQuartos, int *capacidadeQuartos) {
    int opcao;
    int numero;
    int capacidade;
    int indice;
    float diaria;
    TipoQuarto TipoQuarto;


    do {
        printf("\n========== MENU DE QUARTOS ==========\n");
        printf("1 - Cadastrar quarto\n");
        printf("2 - Buscar quarto por numero\n");
        printf("3 - Listar todos os quartos\n");
        printf("4 - Listar quartos disponiveis\n");
        printf("5 - Remover quarto\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }
        

        switch (opcao) {
            case 1: {
                if(!(disponibilidadeQuartos(quartos, *qtdQuartos, capacidadeQuartos))){
                    limparTela();
                    printf("Não é possível cadastrar novos quartos.\n");
                    break;
                }

                printf("\nNúmero do quarto: ");
                scanf("%d", &numero);
                limparEntrada();
               
                if(!(submenuTipoQuarto(&TipoQuarto))){
                    limparTela();
                    printf("Operação cancelada.\n");
                    break;
                }

                printf("Capacidade de pessoas: ");
                scanf("%d", &capacidade);
                limparEntrada();

                printf("Valor da diaria: R$ ");
                scanf("%f", &diaria);
                limparEntrada();

                limparTela();

                if (inserirQuartos(*quartos, qtdQuartos, numero, TipoQuarto, capacidade, diaria)) {
                    printf("Quarto cadastrado com sucesso!\n");

                } else {
                    printf("Não foi possível cadastrar o quarto.\n");
                }

                break;
            }
                
            case 2: {
                if (*qtdQuartos == 0){
                    limparTela();
                    printf("Não há quartos cadastrados.\n");
                    break;
                }
                
                printf("Número do quarto que deseja buscar: ");
                scanf("%d", &numero);
                limparEntrada();

                indice = buscarQuartoNumero(*quartos, *qtdQuartos, numero);

                limparTela();

                if (indice == -1) {
                    printf("Quarto não encontrado.\n");
                    break;
                }

                printf("\nQuarto localizado:\n\n");
                imprimirDadosQuarto(&(*quartos)[indice]);

                break;
            }    

            case 3: {
                limparTela();

                if (*qtdQuartos == 0){
                    printf("Não há quartos cadastrados.\n");
                    break;

                } else {
                    printf("Quartos Cadastrados: %d \n\n", *qtdQuartos);
                    listarQuartos(*quartos, *qtdQuartos, 0);
                } 

                break;
            }

            case 4: {
                limparTela();

                if (*qtdQuartos == 0){
                    printf("Não há quartos cadastrados.\n");
                    break;

                } else {
                    listarQuartos(*quartos, *qtdQuartos, 1);
                }  

                break;
            }

            case 5: {
                if (*qtdQuartos == 0){
                    limparTela();
                    printf("Não há quartos cadastrados.\n");
                    break;
                }

                printf("Número do quarto que deseja remover: ");
                scanf("%d", &numero);
                limparEntrada();
                    
                indice = buscarQuartoNumero(*quartos, *qtdQuartos, numero);

                limparTela();

                if(indice == -1){
                    printf("Quarto não encontrado.\n");
                    break;
                }

                printf("Deseja realmente remover o quarto Nº %d?\n", numero);

                int opcaoQuarto;

                do {
                    printf("\n1 - Confirmar\n");
                    printf("2 - Cancelar\n");
                    printf("\nEscolha uma opção: ");

                    scanf("%d", &opcaoQuarto);
                    limparEntrada();

                    limparTela();

                    switch (opcaoQuarto){
                        case 1:
                            if(removerQuartos(*quartos, qtdQuartos, numero)) {
                                printf("Quarto removido com sucesso.\n");
                            }
                        break;

                        case 2:
                            printf("Operação cancelada. Retornando ao menu quartos.\n");
                        break;

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }        


                } while (opcaoQuarto != 1 && opcaoQuarto != 2);
              
                break;    
            }

            case 0:
                limparTela();
                printf("Voltando ao menu principal...\n");
            break;


            default:
                limparTela();
                printf("Opção inválida. Tente novamente.\n");

        }

    } while (opcao != 0);
}

int main(void) {

    int capacidadeClientes = 100; /*Capacidade inicial de clientes*/
    int qtdClientes = 0; /*Clientes cadastrados*/
    int capacidadeQuartos = 100;
    int qtdQuartos = 0;
    int proximoIdCliente = 100;

    /* Os vetores guardam os registros durante a execução do programa. */
    Cliente *clientes = malloc(capacidadeClientes * sizeof(Cliente));

    if(clientes == NULL){
        printf("Ocorreu um erro na alocação de memória para Clientes.");
        return 0;
    }

    Quarto *quartos = malloc(capacidadeQuartos * sizeof(Quarto));

    if(quartos == NULL){
        printf("Ocorreu um erro na alocação de memória para Quartos.");
        return 0;
    }

    int opcao;

    do {
        printf("\n========================================\n");
        printf("       HOSPEDA - SISTEMA DE HOTEL\n");
        printf("========================================\n");
        printf("\n1 - Gerenciar clientes\n");
        printf("2 - Gerenciar quartos\n");
        printf("0 - Encerrar programa\n");
        printf("\nEscolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                limparTela();
                menuClientes(&clientes, &qtdClientes, &capacidadeClientes, &proximoIdCliente);
            break;

            case 2:
                limparTela();
                menuQuartos(&quartos, &qtdQuartos, &capacidadeQuartos);
            break;

            case 0:
                limparTela();
                printf("Programa encerrado. Obrigado por utilizar o Hospeda!\n");
            break;

            default:
                limparTela();
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    free(clientes);
    free(quartos);
    return 0;
}
