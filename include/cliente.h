#ifndef CLIENTE_H
#define CLIENTE_H
typedef struct
{
    int id;
    char nome[100];
    char cpf[20];
    char telefone[20];
} Cliente;

typedef struct NoCliente
{
    Cliente dados;
    struct NoCliente *proximo;
} NoCliente;

typedef struct
{
    NoCliente *primeiro;
    NoCliente *ultimo;
} ListaClientes;

int inicializarListaClientes(ListaClientes *listaClientes);

int inserirCliente(ListaClientes *listaClientes, int *qtdClientes, int idCliente, char nome[], char cpf[], char telefone[]);

int removerCliente(ListaClientes *listaClientes, int *qtdClientes, int idCliente);

NoCliente *buscarClienteId(ListaClientes *listaClientes, int idCliente);

NoCliente *buscarClienteCpf(ListaClientes *listaClientes, char cpf[]);

NoCliente *buscarClienteNome(ListaClientes *listaClientes, char nome[]);

void listarClientes(ListaClientes *listaClientes);

int validarNome(char nome[]);
void formatarNome(char nome[], char *nomeFormatado);

int validarCpf(char cpf[]);
void formatarCpf(char cpf[], char *cpfFormatado);

int validarTelefone(char telefone[]);
void formatarTelefone(char telefone[], char *telefoneFormatado);

void imprimirDadosCliente(Cliente *cliente);
#endif

