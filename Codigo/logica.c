#ifndef LOGICA_C
#define LOGICA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cafeteria.h"

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
    Item *novo = (Item*)malloc(sizeof(Item));
    
    if (novo == NULL) {
        printf("Erro de memória.\n");
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


#endif 
