#ifndef CAFETERIA_H
#define CAFETERIA_H

typedef struct Item {
    int id_i;             //id 
    char nome[50];        // Nome do item
    float preco;          // Preço do item
    struct Item *proximo; // Para a Lista de Itens
} Item;

typedef struct Pedido {
    int id_p;               // Identificador único do pedido
    char nome_cliente[50];  // Nome do cliente que fez o pedido
    int *itens_id;          //Array dinâmico que guarda os IDs dos produtos
    int quantidade_itens;   // Guarda o tamanho atual do array
    int status;             // 0 - Pendente, 1 - Em preparação, 2 - Pronto para entrega, 3 - Entregue, 4 - Cancelado
    struct Pedido *proximo; // Para a Fila/Lista
} Pedido;

typedef struct {
    Pedido *inicio;                // Ponteiro para o início da fila
    Pedido *fim;                   // Ponteiro para o fim da fila
} FilaPedidos;

// Estrutura para controle de faturamento
typedef struct {
    float vendas[10];       // Guarda as últimas 10 vendas
    int total_vendas;       // Contador de vendas realizadas
} Faturamento;

// Protótipos das funções de Cardápio (teste)
Item* adicionarAoCardapio(Item *lista, int id, char *nome, float preco);
void listarCardapio(Item *lista);
void editarItem(Item *lista, int id);
Item* deletarItem(Item *lista, int id);

// Protótipos das funções de Faturamento
void inicializarFaturamento(Faturamento *f);
void adicionarVenda(Faturamento *f, float valor);
void mostrarRelatorio(Faturamento *f);

#endif
