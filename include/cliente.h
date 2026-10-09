typedef struct {
    int id;
    char nome[100];
    char cpf[20];
    char telefone[20];
} Cliente;

int inserirCliente(Cliente *listaClientes, int *qtdClientes, int idCliente, char nome[], char cpf[], char telefone[]);

int removerCliente(Cliente *listaClientes, int *qtdClientes, int idCliente);

int buscarClienteId(Cliente *listaClientes, int qtdClientes, int idCliente);

int buscarClienteCpf(Cliente *listaClientes, int qtdClientes, char cpf[]);

int buscarClienteNome(Cliente *listaClientes, int qtdClientes, char nome[]);

void listarClientes(Cliente *listaClientes, int qtdClientes);

int validarNome(char nome[]);
void formatarNome(char nome[], char *nomeFormatado);

int validarCpf(char cpf[]);
void formatarCpf(char cpf[], char *cpfFormatado);

int validarTelefone(char telefone[]);
void formatarTelefone(char telefone[], char *telefoneFormatado);

void imprimirDados(Cliente *cliente);
