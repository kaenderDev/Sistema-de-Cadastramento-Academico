#ifndef LOGICA_C
#define LOGICA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cafeteria.h"

// Funções do cardapio e itens


// Função p/ Listar

void listarCardapio(Item *lista) {
    if (lista == NULL) {
        printf("\n--- Cardapio Vazio ---\n");
        return;
    }
    printf("\n--- Itens no Cardapio ---\n");
    Item *atual = lista;
    while (atual != NULL) {
        printf("ID: %d | Nome: %-20s | Preco: R$ %.2f\n", atual->id_i, atual->nome, atual->preco);
        atual = atual->proximo;
    }
    printf("-------------------------\n");
}

//  Busca pelo ID e altera os outros campos
void editarItem(Item *lista, int id) {
    Item *atual = lista;
    while (atual != NULL) {
        if (atual->id_i == id) {
            printf("Editando item ID %d (%s):\n", id, atual->nome);
            printf("Novo Nome: ");
            scanf(" %[^\n]s", atual->nome); // Lê string com espaços
            printf("Novo Preco: ");
            scanf("%f", &atual->preco);
            printf("Item atualizado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Erro: Item com ID %d nao encontrado.\n", id);
}

// Função p/ Deletar
Item* deletarItem(Item *lista, int id) {
    Item *atual = lista;
    Item *anterior = NULL;

    while (atual != NULL) {
        if (atual->id_i == id) {
            if (anterior == NULL) {
                // Caso o item a ser removido seja o primeiro da lista
                lista = atual->proximo;
            } else {
                // Remove o item do meio ou do fim
                anterior->proximo = atual->proximo;
            }
            free(atual); // Libera a memória
            printf("Item ID %d removido do cardapio.\n", id);
            return lista;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Erro: Item com ID %d nao encontrado.\n", id);
    return lista;
}

// O ponteiro retorna para que o 'main' sempre tenha o endereço atualizado do início do cardápio
Item* adicionarAoCardapio(Item *inicio, int id, char *nome, float preco) {
    // Verificação de ID duplicado
    Item *atual = inicio;
    while(atual != NULL){
        if (atual -> id_i == id) {
            printf ("\nErro: O id %d ja existe no cardapio!\n", id);
            return inicio;
        }
        atual= atual->proximo;
    }

     // Se não for duplicado, cria o novo Item
    Item *novo = (Item*)malloc(sizeof(Item));
    if (novo == NULL) {
        printf("Erro de memoria.\n");
        return inicio;
    }

    // Atribuição dos dados
    novo->id_i = id;
    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';
    novo->preco = preco;

    // Faz o encadeamento
    novo->proximo = inicio;
    
    // O novo item agora é o primeiro da lista
    return novo; 
}

// Libera toda a memória alocada para o cardápio
void limparCardapio(Item *lista) {
    Item *atual = lista;
    while (atual != NULL) {
        Item *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Funções do faturamento


// Inicializa o sistema de faturamento zerado
void inicializarFaturamento(Faturamento *f) {
    int i;
    for (i = 0; i < 10; i++) {
        f->vendas[i] = 0.0;
    }
    f->total_vendas = 0;
}

// Adiciona uma venda no array de faturamento
void adicionarVenda(Faturamento *f, float valor) {
    int indice = f->total_vendas % 10; // Usa o resto pra circular no array
    f->vendas[indice] = valor;
    f->total_vendas++;
    printf("Venda de R$ %.2f registrada com sucesso!\n", valor);
}

// Mostra o relatório com as últimas vendas
void mostrarRelatorio(Faturamento *f) {
    int i;
    float total = 0.0;
    int qtd = (f->total_vendas < 10) ? f->total_vendas : 10;
    
    printf("\n========== RELATORIO DE VENDAS ==========\n");
    
    if (f->total_vendas == 0) {
        printf("Nenhuma venda registrada ainda.\n");
        printf("=========================================\n");
        return;
    }
    
    printf("Ultimas %d vendas:\n", qtd);
    for (i = 0; i < qtd; i++) {
        printf("Venda %d: R$ %.2f\n", i+1, f->vendas[i]);
        total += f->vendas[i];
    }
    
    printf("-----------------------------------------\n");
    printf("Total arrecadado: R$ %.2f\n", total);
    printf("Media por venda: R$ %.2f\n", total/qtd);
    printf("=========================================\n");
}

// Funcoes do cancelamento

void inicializarPilha(PilhaCancelamento *p) {
    p->topo = NULL;
}

// Verifica se está vazia
int pilhaVazia(PilhaCancelamento *p) {
    return p->topo == NULL;
}

// Empilha pedido cancelado
void empilharCancelamento(PilhaCancelamento *p, Pedido *pedido) {
    if (pedido == NULL) return;
    
    pedido->status = 4; 
    pedido->proximo = p->topo; 
    p->topo = pedido; 

    printf("Pedido %d empilhado (cancelado).\n", pedido->id_p);
}

// Remove da pilha

Pedido* removerCancelamento(PilhaCancelamento *p) {
    
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return NULL;
    }

    Pedido *removido = p->topo;
    p->topo = removido->proximo;
    removido->proximo = NULL;
    removido->status = 1;

    return removido;
}

// Mostra a pilha
    
void mostrarCancelamentos(PilhaCancelamento *p) {
    
    Pedido *atual = p->topo;
    printf("\n--- Pilha de Cancelamentos ---\n");

    while (atual != NULL) {
        printf("Pedido ID: %d | Cliente: %s\n",
               atual->id_p,
               atual->nome_cliente);

        atual = atual->proximo;
    }
}

//limpar Cancelamentos

void limparCancelamentos(PilhaCancelamento *p) {
    while (!pilhaVazia(p)) {
        Pedido *removido = removerCancelamento(p);
        destruirPedido(removido);
    }
}

// Funções Pedidos e Fila

int proximo_id_pedido = 1;
// Cria novo pedido
Pedido* criarPedido(char *nome_cliente){
    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if(novo == NULL){
        printf("Erro ao alocar memoria para o pedido.\n");
        return NULL;
    }

    novo->id_p = proximo_id_pedido++;
    strcpy(novo->nome_cliente, nome_cliente);

    novo->itens_id = NULL;
    novo->quantidade_itens = 0;

    novo->status = 0;
    novo->proximo = NULL;

    return novo;
}

// Adiciona item ao pedido
void adicionarItemAoPedido(Pedido *p, int id_i, Item *cardapio){

    //Verifica se o id do item existe

    Item *atual = cardapio;
    int encontrado = 0;
    while ( atual!= NULL){
        if (atual -> id_i == id_i){
            encontrado = 1 ;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado){
        printf("Erro: Item com ID %d nao existe no cardapio!\n", id_i);
        return;
    } 
    p->quantidade_itens++;

    int *temp = (int*)realloc(p->itens_id, p->quantidade_itens * sizeof(int));

    if(temp == NULL){
        printf("Erro ao adicionar item.\n");
        p->quantidade_itens--;
        return;
    }

    p->itens_id = temp;

    p->itens_id[p->quantidade_itens - 1] = id_i;

    printf("Item %d adicionado ao pedido de %s.\n", id_i, p->nome_cliente);
}

// Inicializa a fila
void inicializarFila(FilaPedidos *f){
    f->inicio = NULL;
    f->fim = NULL;
}

// Enfileira os pedidos
void enfileirarPedido(FilaPedidos *f, Pedido *p){
    if(p->quantidade_itens == 0){
        printf("Erro: O pedido #%d nao possui itens e nao pode ser enfileirado.\n", p->id_p);
        
        free(p); 
        
        return;
    }
    
    p->proximo = NULL;

    if(f->inicio == NULL){
        f->inicio = p;
        f->fim = p;
    } else{
        f->fim->proximo = p;
        f->fim = p;
    }

    p->status = 1;

    printf("Pedido #%d (Cliente: %s) entrou na fila de preparacao.\n", p->id_p, p->nome_cliente);
}

// Calcula o total do pedido com base nos ids dos itens no array dinamico
// e seus preços no cardápio
float calcularTotalPedido(Pedido *p, Item *cardapio) {
    float total = 0.0;

    for (int i = 0; i < p->quantidade_itens; i++) {
        int id_procurado = p->itens_id[i];
        Item *atual = cardapio;

        while (atual != NULL) {
            if (atual->id_i == id_procurado) {
                total += atual->preco;
                break;
            }
            atual = atual->proximo;
        }
    }
    return total;
}

// Finalizar o pedido da fila
Pedido* desenfileirarPedido(FilaPedidos *f){
    if(f->inicio == NULL){
        printf("A fila de pedidos esta vazia!\n");
        return NULL;
    }

    Pedido *pedidoRemovido = f->inicio;

    f->inicio = f->inicio->proximo;

    if(f->inicio == NULL){
        f->fim = NULL;
    }

    pedidoRemovido->proximo = NULL;

    pedidoRemovido->status = 2;

    return pedidoRemovido;
}

// Libera a memória alocada para o pedido e seu array de itens
void destruirPedido(Pedido *p) {
    if (p != NULL) {
        if (p->itens_id != NULL) {
            free(p->itens_id); 
        }
        free(p); 
    }
}

// Listar os pedidos em fila
void listarFilaPedidos(FilaPedidos *f, Item *cardapio) {
    if (f->inicio == NULL) {
        printf("\n--- Fila de Pedidos Vazia ---\n");
        return;
    }

    printf("\n--- Fila de Preparacao ---\n");
    Pedido *atual = f->inicio;
    while (atual != NULL) {
        
        float total = calcularTotalPedido(atual, cardapio);
        
        printf("ID: %d | Cliente: %-10s | Itens: %d | Total: R$ %.2f\n", 
               atual->id_p, 
               atual->nome_cliente, 
               atual->quantidade_itens, 
               total);
               
        atual = atual->proximo;
    }
    printf("--------------------------\n");
}

// libera a fila 
void limparFila(FilaPedidos *f) {
    while (f->inicio != NULL) {
        Pedido *removido = desenfileirarPedido(f);
        destruirPedido(removido);
    }
}

#endif 
