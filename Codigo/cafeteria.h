#ifndef CAFETERIA_H
#define CAFETERIA_H

typedef struct Item {
    char nome[50];        // Nome do item
    float preco;          // Preço do item
    struct Item *proximo; // Para a Lista de Itens
} Item;

typedef struct Pedido {
    int id;                 // Identificador único do pedido
    char nome_cliente[50];  // Nome do cliente que fez o pedido
    float *itens_precos;    // Ponteiro que apontará para o bloco de memória do array
    int quantidade_itens;   // Guarda o tamanho atual do array
    int status;             // 0 - Pendente, 1 - Em preparação, 2 - Pronto para entrega, 3 - Entregue, 4 - Cancelado
    struct Pedido *proximo; // Para a Fila/Lista
} Pedido;

typedef struct {
    Pedido *inicio;                // Ponteiro para o início da fila
    Pedido *fim;                   // Ponteiro para o fim da fila
} FilaPedidos;

#endif