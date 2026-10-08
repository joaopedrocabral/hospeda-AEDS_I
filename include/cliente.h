typedef struct {
    int id;
    char nome[100];
    char cpf[14];
    char telefone[20];
} Cliente;

void inserirCliente();

void removerCliente();

Cliente* buscarClienteId();

Cliente* buscarClienteCpf();

Cliente* buscarClienteNome();

void listarClientes();

int validarNome();
void formatarNome();

void validarCpf();
void formatarCpf();

void validarTelefone();
void formatarTelefone();
