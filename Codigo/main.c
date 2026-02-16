#include <stdio.h>
#include "cafeteria.h"
#include <string.h>
#include <stdlib.h>

int main() {
    Item *cardapio = NULL;
    FilaPedidos fila;
    inicializarFila(&fila);
    
    
    // 1. Teste de Adição
    cardapio = adicionarAoCardapio(cardapio, 1, "Cafe", 5.0);
    cardapio = adicionarAoCardapio(cardapio, 2, "Bolo", 10.0);
    
    // 2. Listagem Inicial
    listarCardapio(cardapio);

    // 3. Teste de Edição
    printf("\nEditando o item 1...\n");
    editarItem(cardapio, 1);
    
    // 4. Teste de Remoção
    printf("\nRemovendo o item 2...\n");
    cardapio = deletarItem(cardapio, 2);

    // 5. Resultado Final
    listarCardapio(cardapio);
    
    //Testes de cancelamento
    
    Pedido pedido; // pedido de teste
    pedido.id_p = 1;
    pedido.status = 0;
    pedido.quantidade_itens = 0;
    pedido.itens_id = NULL;
    strcpy(pedido.nome_cliente, "Teste");
    
    PilhaCancelamento pilha; 
    inicializarPilha(&pilha);
    mostrarCancelamentos(&pilha); //retornar vazio
    empilharCancelamento(&pilha, &pedido); //adiciona o pedido
    mostrarCancelamentos(&pilha); //retornar pedido 01
    
    Pedido *removido = removerCancelamento(&pilha); //remove 01
    if (removido != NULL) {
    free(removido->itens_id);
    free(removido);
    }
    
    mostrarCancelamentos(&pilha); //retornar vazio

    // Teste de Pedidos
    Pedido *p1 = criarPedido(101, "Ana");
    adicionarItemAoPedido(p1, 1);
    
    Pedido *p2 = criarPedido(102, "Carlos");
    adicionarItemAoPedido(p2, 1);

    enfileirarPedido(&fila, p1);
    enfileirarPedido(&fila, p2);

    listarFilaPedidos(&fila);

    printf("\nEntregando pedido...\n");
    Pedido *entregue = desenfileirarPedido(&fila);
    
    if (entregue != NULL) {
        printf("Pedido #%d da %s foi entregue!\n", entregue->id_p, entregue->nome_cliente);
        
        free(entregue->itens_id); // Libera o array de itens
        free(entregue);           // Libera a struct pedido
    }

    listarFilaPedidos(&fila);

    return 0;
}

