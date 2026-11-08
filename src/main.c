#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "quarto.h"
#include "historico.h"
#include "reserva.h"
#include "Espera.h"

// Le um numero e evita problemas quando a pessoa digita letras.
int lerNumero(const char *pergunta) {
    char linha[80];
    int numero;
    printf("%s", pergunta);
    if (fgets(linha, sizeof(linha), stdin) == NULL) return -1;
    if (sscanf(linha, "%d", &numero) != 1) return -1;
    return numero;
}

// Le texto sem guardar o Enter no final.
void lerTexto(const char *pergunta, char *texto, int tamanho) {
    printf("%s", pergunta);
    if (fgets(texto, tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }
    texto[strcspn(texto, "\n")] = '\0';
}

// Registra apenas operacoes que deram certo.
void salvarHistorico(PilhaHistorico *historico, const char *modulo,
                    const char *operacao, const char *descricao) {
    if (!registrarOperacao(historico, modulo, operacao, descricao)) {
        printf("Aviso: nao foi possivel salvar o historico.\n");
    }
}

void menuClientes(ListaClientes *clientes, int *quantidade,
                  int *proximoId, PilhaHistorico *historico) {
    int opcao;
    do {
        printf("\n=== CLIENTES ===\n1 - Cadastrar\n2 - Buscar por ID\n3 - Listar\n4 - Remover\n5 - Buscar por nome\n6 - Buscar por CPF\n0 - Voltar\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) {
            char nome[100], cpf[20], telefone[20], descricao[150];
            lerTexto("Nome: ", nome, sizeof(nome));
            lerTexto("CPF (11 digitos): ", cpf, sizeof(cpf));
            lerTexto("Telefone (10 ou 11 digitos): ", telefone, sizeof(telefone));
            if (inserirCliente(clientes, quantidade, *proximoId, nome, cpf, telefone)) {
                printf("Cliente cadastrado! ID: %d\n", *proximoId);
                snprintf(descricao, sizeof(descricao), "Cliente %d cadastrado: %.95s", *proximoId, nome);
                salvarHistorico(historico, "Clientes", "Cadastro", descricao);
                (*proximoId)++;
            } else printf("Cadastro nao realizado.\n");
        } else if (opcao == 2) {
            int id = lerNumero("ID: ");
            NoCliente *encontrado = buscarClienteId(clientes, id);
            if (encontrado) imprimirDadosCliente(&encontrado->dados);
            else printf("Cliente nao encontrado.\n");
        } else if (opcao == 3) {
            if (*quantidade == 0) printf("Nenhum cliente cadastrado.\n");
            else {
                NoCliente *atual = clientes->primeiro->proximo;
                while (atual) {
                    imprimirDadosCliente(&atual->dados);
                    printf("\n");
                    atual = atual->proximo;
                }
            }
        } else if (opcao == 4) {
            int id = lerNumero("ID do cliente: ");
            NoCliente *encontrado = buscarClienteId(clientes, id);
            if (!encontrado) { printf("Cliente nao encontrado.\n"); continue; }
            if (lerNumero("Confirmar remocao? 1=Sim, 2=Nao: ") != 1) continue;
            if (removerCliente(clientes, quantidade, id)) {
                char descricao[150];
                snprintf(descricao, sizeof(descricao), "Cliente %d removido", id);
                salvarHistorico(historico, "Clientes", "Remocao", descricao);
                printf("Cliente removido.\n");
            }
        } else if (opcao == 5 || opcao == 6) {
            char termo[100];
            lerTexto(opcao == 5 ? "Nome: " : "CPF: ", termo, sizeof(termo));
            NoCliente *encontrado = opcao == 5 ? buscarClienteNome(clientes, termo) : buscarClienteCpf(clientes, termo);
            if (encontrado) imprimirDadosCliente(&encontrado->dados);
            else printf("Cliente nao encontrado.\n");
        } else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
}

void listarQuartosDisponiveis(Quarto *raiz);

void menuQuartos(Quarto **raiz, PilhaHistorico *historico) {
    int opcao;
    do {
        printf("\n=== QUARTOS ===\n1 - Cadastrar\n2 - Buscar\n3 - Listar\n4 - Remover\n5 - Listar disponiveis\n0 - Voltar\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) {
            int numero = lerNumero("Numero do quarto: ");
            if (numero <= 0 || buscarQuartoNumero(*raiz, numero)) {
                printf("Numero invalido ou quarto ja cadastrado.\n"); continue;
            }
            int tipo = lerNumero("Tipo: 1=Standard, 2=Deluxe, 3=Premium: ");
            int capacidade = lerNumero("Capacidade: ");
            char linha[80]; float diaria;
            lerTexto("Valor da diaria (ex: 150.00): ", linha, sizeof(linha));
            if (tipo < 1 || tipo > 3 || capacidade <= 0 ||
                sscanf(linha, "%f", &diaria) != 1 || diaria <= 0) {
                printf("Dados invalidos.\n"); continue;
            }
            Quarto *novo = criarQuarto(numero, (TipoQuarto)(tipo - 1), capacidade, diaria, DISPONIVEL);
            if (!novo) { printf("Erro de memoria.\n"); continue; }
            *raiz = inserirQuartos(*raiz, novo);
            if (buscarQuartoNumero(*raiz, numero)) {
                char descricao[150];
                snprintf(descricao, sizeof(descricao), "Quarto %d cadastrado", numero);
                salvarHistorico(historico, "Quartos", "Cadastro", descricao);
                printf("Quarto cadastrado.\n");
            }
        } else if (opcao == 2) {
            int numero = lerNumero("Numero: ");
            Quarto *quarto = buscarQuartoNumero(*raiz, numero);
            if (quarto) imprimirDadosQuarto(quarto);
            else printf("Quarto nao encontrado.\n");
        } else if (opcao == 3) {
            if (!*raiz) printf("Nenhum quarto cadastrado.\n");
            else listarQuartos(*raiz);
        } else if (opcao == 4) {
            int numero = lerNumero("Numero do quarto: ");
            Quarto *quarto = buscarQuartoNumero(*raiz, numero);
            if (!quarto) { printf("Quarto nao encontrado.\n"); continue; }
            if (quarto->Status != DISPONIVEL) {
                printf("Somente quartos disponiveis podem ser removidos.\n"); continue;
            }
            if (lerNumero("Confirmar remocao? 1=Sim, 2=Nao: ") != 1) continue;
            *raiz = removerQuartos(*raiz, numero);
            if (!buscarQuartoNumero(*raiz, numero)) {
                char descricao[150];
                snprintf(descricao, sizeof(descricao), "Quarto %d removido", numero);
                salvarHistorico(historico, "Quartos", "Remocao", descricao);
                printf("Quarto removido.\n");
            }
        } else if (opcao == 5) {
            // Percorre a arvore sem alterar os quartos.
            listarQuartosDisponiveis(*raiz);
        } else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
}

void menuHistorico(PilhaHistorico *historico) {
    int opcao;
    do {
        printf("\n=== HISTORICO (PILHA) ===\n1 - Listar operacoes\n2 - Buscar por ID\n0 - Voltar\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) listarHistorico(historico);
        else if (opcao == 2) buscarHistorico(historico, lerNumero("ID do registro: "));
        else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
}


void listarQuartosDisponiveis(Quarto *raiz) {
    if (!raiz) return;
    listarQuartosDisponiveis(raiz->esq);
    if (raiz->Status == DISPONIVEL) imprimirDadosQuarto(raiz);
    listarQuartosDisponiveis(raiz->dir);
}

void menuReservas(ListaReservas *reservas, ListaClientes *clientes, Quarto *quartos,
                  int *proximoId, PilhaHistorico *historico) {
    int opcao;
    do {
        printf("\n=== RESERVAS ===\n1 - Criar\n2 - Buscar por ID\n3 - Listar\n4 - Cancelar\n5 - Check-in\n6 - Check-out\n7 - Listar por cliente\n0 - Voltar\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) {
            int cliente = lerNumero("ID do cliente: ");
            int quarto = lerNumero("Numero do quarto: ");
            char entrada[20], saida[20], descricao[150];
            lerTexto("Check-in (dd/mm/aaaa): ", entrada, sizeof(entrada));
            lerTexto("Check-out previsto (dd/mm/aaaa): ", saida, sizeof(saida));
            if (!validarDatasReserva(entrada, saida)) {
                printf("Datas invalidas.\n"); continue;
            }
            if (criarReserva(reservas, clientes, quartos, *proximoId, cliente, quarto, entrada, saida)) {
                snprintf(descricao, sizeof(descricao), "Reserva %d criada para cliente %d, quarto %d", *proximoId, cliente, quarto);
                salvarHistorico(historico, "Reservas", "Cadastro", descricao);
                (*proximoId)++;
            }
        } else if (opcao == 2) {
            NoReserva *r = buscarReservaId(reservas, lerNumero("ID: "));
            if (r) imprimirDadosReserva(&r->dados, clientes);
            else printf("Reserva nao encontrada.\n");
        } else if (opcao == 3) {
            listarReservas(reservas, clientes);
        } else if (opcao == 7) {
            listarReservasCliente(reservas, clientes, lerNumero("ID do cliente: "));
        } else if (opcao >= 4 && opcao <= 6) {
            int id = lerNumero("ID da reserva: ");
            int sucesso = 0;
            const char *acao = opcao == 4 ? "Cancelamento" : opcao == 5 ? "Check-in" : "Check-out";
            if (opcao == 4) sucesso = cancelarReserva(reservas, id);
            if (opcao == 5) sucesso = realizarCheckIn(reservas, id);
            if (opcao == 6) {
                char data[20];
                lerTexto("Data de check-out (dd/mm/aaaa): ", data, sizeof(data));
                if (strlen(data) == 10) sucesso = realizarCheckOut(reservas, id, data, quartos);
                else printf("Data invalida.\n");
            }
            if (sucesso) {
                char descricao[150];
                snprintf(descricao, sizeof(descricao), "Reserva %d: %s", id, acao);
                salvarHistorico(historico, "Reservas", acao, descricao);
                printf("Operacao realizada.\n");
            }
        } else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
}

void menuEspera(FilaEspera *fila, ListaClientes *clientes, Quarto *quartos,
               int *proximoId, PilhaHistorico *historico) {
    int opcao;
    do {
        printf("\n=== FILA DE ESPERA ===\n1 - Adicionar\n2 - Listar\n3 - Buscar por ID\n4 - Atender proximo\n0 - Voltar\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) {
            int cliente = lerNumero("ID do cliente: ");
            int quarto = lerNumero("Numero do quarto: ");
            if (!buscarClienteId(clientes, cliente) || !buscarQuartoNumero(quartos, quarto)) {
                printf("Cliente ou quarto inexistente.\n"); continue;
            }
            char entrada[20], saida[20], descricao[150];
            lerTexto("Entrada (dd/mm/aaaa): ", entrada, sizeof(entrada));
            lerTexto("Saida (dd/mm/aaaa): ", saida, sizeof(saida));
            if (!validarDatasReserva(entrada, saida)) {
                printf("Datas invalidas.\n"); continue;
            }
            Espera *nova = criarSolicitacao(*proximoId, cliente, quarto, entrada, saida);
            if (!nova) { printf("Falha ao criar solicitacao.\n"); continue; }
            enfilerar(fila, nova);
            snprintf(descricao, sizeof(descricao), "Solicitacao %d adicionada a fila", *proximoId);
            salvarHistorico(historico, "Espera", "Entrada", descricao);
            (*proximoId)++;
        } else if (opcao == 2) listarFila(fila);
        else if (opcao == 3) {
            Espera *e = buscarSolicitacao(fila, lerNumero("ID da solicitacao: "));
            if (e) imprimirSolicitacao(e);
            else printf("Solicitacao nao encontrada.\n");
        } else if (opcao == 4) {
            Espera *e = desenfilerar(fila);
            if (!e) printf("Fila vazia.\n");
            else {
                char descricao[150];
                snprintf(descricao, sizeof(descricao), "Solicitacao %d retirada da fila", e->IdSolicitacao);
                salvarHistorico(historico, "Espera", "Saida", descricao);
                imprimirSolicitacao(e);
                free(e);
            }
        } else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
}

void liberarReservas(ListaReservas *reservas) {
    NoReserva *atual = reservas->primeiro;
    while (atual) { NoReserva *proximo = atual->proximo; free(atual); atual = proximo; }
}

void liberarEspera(FilaEspera *fila) {
    Espera *atual;
    while ((atual = desenfilerar(fila)) != NULL) free(atual);
}

// Libera os nos da lista, inclusive o no inicial vazio.
void liberarClientes(ListaClientes *clientes) {
    NoCliente *atual = clientes->primeiro;
    while (atual) {
        NoCliente *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Libera os quartos da arvore.
void liberarQuartos(Quarto *raiz) {
    if (!raiz) return;
    liberarQuartos(raiz->esq);
    liberarQuartos(raiz->dir);
    free(raiz);
}

int main(void) {
    ListaClientes clientes;
    Quarto *quartos = NULL;
    PilhaHistorico historico;
    ListaReservas reservas;
    FilaEspera fila;
    int proximoIdReserva = 1, proximoIdEspera = 1;
    int quantidadeClientes = 0, proximoIdCliente = 1, opcao;
    if (!inicializarListaClientes(&clientes)) return 1;
    iniciarHistorico(&historico);
    if (!inicializarListaReservas(&reservas)) { liberarClientes(&clientes); return 1; }
    iniciarFila(&fila);
    do {
        printf("\n====== HOSPEDA ======\n1 - Clientes\n2 - Quartos\n3 - Historico de operacoes\n4 - Reservas\n5 - Fila de espera\n0 - Sair\n");
        opcao = lerNumero("Opcao: ");
        if (opcao == 1) menuClientes(&clientes, &quantidadeClientes, &proximoIdCliente, &historico);
        else if (opcao == 2) menuQuartos(&quartos, &historico);
        else if (opcao == 3) menuHistorico(&historico);
        else if (opcao == 4) menuReservas(&reservas, &clientes, quartos, &proximoIdReserva, &historico);
        else if (opcao == 5) menuEspera(&fila, &clientes, quartos, &proximoIdEspera, &historico);
        else if (opcao != 0) printf("Opcao invalida.\n");
    } while (opcao != 0);
    liberarHistorico(&historico);
    liberarReservas(&reservas);
    liberarEspera(&fila);
    liberarClientes(&clientes);
    liberarQuartos(quartos);
    printf("Programa encerrado.\n");
    return 0;
}
