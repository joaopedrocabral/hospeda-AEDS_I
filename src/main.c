/*
 * Projeto Hospeda - Sistema de Gerenciamento de Hotel
 * Arquivo: main.c
 *
 * Este arquivo contém o menu principal do programa.
 * As funções de cadastro, busca, listagem e remoção ficam
 * implementadas nos arquivos cliente.c e quarto.c.
 */

#include <stdio.h>
#include <string.h>

#include "include/cliente.h"
#include "include/quarto.h"

/* Quantidade máxima de registros que os vetores podem guardar. */
#define MAX_CLIENTES 100
#define MAX_QUARTOS 100

/* Lê um texto com espaços e remove o '\n' colocado pelo fgets. */
void lerTexto(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

/* Limpa caracteres que ficaram no teclado depois de um scanf. */
void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Apenas descarta os caracteres restantes. */
    }
}

/* Menu com as operações de clientes. */
void menuClientes(Cliente clientes[], int *qtdClientes) {
    int opcao;
    int id;
    int indice;
    char nome[100];
    char cpf[20];
    char telefone[20];

    do {
        printf("\n========== MENU DE CLIENTES ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Buscar cliente por ID\n");
        printf("3 - Listar clientes\n");
        printf("4 - Remover cliente\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                /* Impede ultrapassar o tamanho do vetor de clientes. */
                if (*qtdClientes >= MAX_CLIENTES) {
                    printf("Limite de clientes atingido.\n");
                    break;
                }

                printf("ID do cliente: ");
                if (scanf("%d", &id) != 1) {
                    limparEntrada();
                    printf("ID invalido.\n");
                    break;
                }
                limparEntrada();

                /* Verifica se o ID já está cadastrado. */
                if (buscarClienteId(clientes, *qtdClientes, id) != -1) {
                    printf("Ja existe um cliente com esse ID.\n");
                    break;
                }

                printf("Nome completo: ");
                lerTexto(nome, sizeof(nome));

                printf("CPF (somente numeros ou com espacos): ");
                lerTexto(cpf, sizeof(cpf));

                printf("Telefone (somente numeros ou com espacos): ");
                lerTexto(telefone, sizeof(telefone));

                /* A função do arquivo cliente.c valida e cadastra os dados. */
                if (inserirCliente(clientes, qtdClientes, id,
                                   nome, cpf, telefone)) {
                    printf("Cliente cadastrado com sucesso!\n");
                } else {
                    printf("Nao foi possivel cadastrar o cliente.\n");
                }
                break;

            case 2:
                printf("Digite o ID do cliente: ");
                if (scanf("%d", &id) != 1) {
                    limparEntrada();
                    printf("ID invalido.\n");
                    break;
                }
                limparEntrada();

                indice = buscarClienteId(clientes, *qtdClientes, id);
                if (indice != -1) {
                    printf("\n--- Dados do cliente ---\n");
                    imprimirDados(&clientes[indice]);
                }
                break;

            case 3:
                if (*qtdClientes == 0) {
                    printf("Nenhum cliente cadastrado.\n");
                } else {
                    listarClientes(clientes, *qtdClientes);
                }
                break;

            case 4:
                printf("ID do cliente que deseja remover: ");
                if (scanf("%d", &id) != 1) {
                    limparEntrada();
                    printf("ID invalido.\n");
                    break;
                }
                limparEntrada();

                if (removerCliente(clientes, qtdClientes, id)) {
                    printf("Cliente removido com sucesso.\n");
                } else {
                    printf("Nao foi possivel remover: cliente nao encontrado.\n");
                }
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

/* Menu com as operações de quartos. */
void menuQuartos(Quarto quartos[]) {
    int opcao;
    int numero;
    int capacidade;
    int indice;
    int tipoEscolhido;
    float diaria;
    TipoQuarto tipo;
    StatusQuarto status;

    do {
        printf("\n========== MENU DE QUARTOS ==========\n");
        printf("1 - Cadastrar quarto\n");
        printf("2 - Buscar quarto por numero\n");
        printf("3 - Listar todos os quartos\n");
        printf("4 - Listar quartos disponiveis\n");
        printf("5 - Remover quarto\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                printf("Numero do quarto: ");
                if (scanf("%d", &numero) != 1) {
                    limparEntrada();
                    printf("Numero invalido.\n");
                    break;
                }

                printf("Tipo do quarto (0 - Standard, 1 - Deluxe, 2 - Premium): ");
                if (scanf("%d", &tipoEscolhido) != 1 ||
                    tipoEscolhido < 0 || tipoEscolhido > 2) {
                    limparEntrada();
                    printf("Tipo invalido.\n");
                    break;
                }

                printf("Capacidade de pessoas: ");
                if (scanf("%d", &capacidade) != 1 || capacidade <= 0) {
                    limparEntrada();
                    printf("Capacidade invalida.\n");
                    break;
                }

                printf("Valor da diaria: R$ ");
                if (scanf("%f", &diaria) != 1 || diaria <= 0) {
                    limparEntrada();
                    printf("Valor da diaria invalido.\n");
                    break;
                }
                limparEntrada();

                tipo = (TipoQuarto)tipoEscolhido;
                status = DISPONIVEL;

                /*
                 * A função de cadastro de quartos está em quarto.c.
                 * Ela deve armazenar os dados e atualizar a quantidade interna.
                 */
                if (inserirQuartos(quartos, numero, tipo,
                                   capacidade, diaria, status)) {
                    printf("Solicitacao de cadastro concluida.\n");
                } else {
                    printf("Nao foi possivel cadastrar o quarto.\n");
                }
                break;

            case 2:
                printf("Numero do quarto que deseja buscar: ");
                if (scanf("%d", &numero) != 1) {
                    limparEntrada();
                    printf("Numero invalido.\n");
                    break;
                }
                limparEntrada();

                indice = buscarQuartoNumero(quartos, numero);
                if (indice == -1) {
                    printf("Quarto nao encontrado.\n");
                }
                break;

            case 3:
                /* O valor -1 indica que a listagem não deve filtrar o status. */
                listarQuarto(quartos, (StatusQuarto)-1);
                break;

            case 4:
                listarQuarto(quartos, DISPONIVEL);
                break;

            case 5:
                printf("Numero do quarto que deseja remover: ");
                if (scanf("%d", &numero) != 1) {
                    limparEntrada();
                    printf("Numero invalido.\n");
                    break;
                }
                limparEntrada();

                if (removerQuartos(quartos, numero, DISPONIVEL)) {
                    printf("Solicitacao de remocao concluida.\n");
                } else {
                    printf("Nao foi possivel remover o quarto.\n");
                }
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

/* Função principal: inicia os vetores e apresenta o menu geral. */
int main(void) {
    /* Os vetores guardam os registros durante a execução do programa. */
    Cliente clientes[MAX_CLIENTES];
    Quarto quartos[MAX_QUARTOS];

    /* No início, ainda não existe nenhum cliente cadastrado. */
    int qtdClientes = 0;
    int opcao;

    do {
        printf("\n========================================\n");
        printf("       HOSPEDA - SISTEMA DE HOTEL\n");
        printf("========================================\n");
        printf("1 - Gerenciar clientes\n");
        printf("2 - Gerenciar quartos\n");
        printf("0 - Encerrar programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero.\n");
            continue;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                menuClientes(clientes, &qtdClientes);
                break;

            case 2:
                menuQuartos(quartos);
                break;

            case 0:
                printf("Programa encerrado. Obrigado por utilizar o Hospeda!\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
