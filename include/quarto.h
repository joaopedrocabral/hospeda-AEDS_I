#ifndef QUARTO_H
#define QUARTO_H

typedef enum {
    STANDARD,
    DELUXE,
    PREMIUM
}TipoQuarto;

typedef enum {
    DISPONIVEL,
    RESERVADO,
    OCUPADO
}StatusQuarto;

/*Campo Numero é utilizado como chave para organização da árvore, os ponteiros esq e dir referenciam os filhos esquerdo e direito.*/

typedef struct Quarto {
    int Numero;
    int Andar;
    TipoQuarto Tipo;
    int Capacidade;
    float Diaria;
    StatusQuarto Status;
    struct Quarto *esq;
    struct Quarto *dir;
}Quarto;

/*Cria dinamicamente um novo nó (quarto) da árvore. O andar é calculado automaticamente a partir do número do quarto. Retorna:
- Ponteiro para o novo quarto criado.
- NULL em caso de falha na alocação.*/
Quarto *criarQuarto(int Numero, TipoQuarto Tipo, int Capacidade, float Diaria, StatusQuarto Status);

/*Insere um novo quarto na Árvore Binária de Busca.O número do quarto é utilizado como chave de ordenação.Retorna:
- A raiz atualizada da árvore.*/
Quarto *inserirQuartos(Quarto *raiz,Quarto *novo);

/*Busca um quarto pelo número.Retorna:
- Ponteiro para o quarto encontrado.
- NULL caso o quarto não exista.*/
Quarto *buscarQuartoNumero(Quarto *raiz, int Numero);

/*Lista todos os quartos cadastrados em ordem crescente de número através do percurso em ordem (in-order).*/
void listarQuartos(Quarto *raiz);

void imprimirDadosQuarto(Quarto *quarto);

/*Remove um quarto da árvore.A remoção só é permitida para quartos disponíveis.Retorna:
- A raiz atualizada da árvore após a remoção.*/
Quarto *removerQuartos(Quarto *raiz, int Numero);

/*Localiza o menor quarto de uma subárvore.Utilizada principalmente durante a remoção de nós com dois filhos para encontrar o sucessor em ordem.Retorna:
- Ponteiro para o menor nó encontrado.*/
Quarto *menorQuarto(Quarto *raiz);

/*obtém o andar correspondente ao número do quarto.Exemplo:101 -> 1/205 -> 2/312 -> 3*/
int obterAndar(int Numero);


#endif