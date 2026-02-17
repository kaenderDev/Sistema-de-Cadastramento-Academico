#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cafeteria.h"
#include "logica.c"

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar(); // Limpa o buffer
    getchar(); // Aguarda a entrada
}

int main() {
    Item *cardapio = NULL;
    FilaPedidos fila;
    Faturamento fat;
    PilhaCancelamento pilha;

    inicializarFila(&fila);
    inicializarFaturamento(&fat);
    inicializarPilha(&pilha);

    int menu_principal, sub;

    do {
        system("clear || cls");
        printf("\n--- SISTEMA CAFETERIA ---\n");
        printf("1. Gerenciar Cardapio\n");
        printf("2. Pedidos e Fila\n");
        printf("3. Financeiro\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &menu_principal);

        switch (menu_principal) {
            case 1:
                do {
                    system("clear || cls");
                    printf("--- Gerenciar Cardapio ---\n");
                    printf("1. Adicionar Item \n");
                    printf("2. Listar Itens\n");
                    printf("3. Editar Item\n");
                    printf("4. Remover Item\n");
                    printf("0. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &sub);

                    if (sub == 1) {
                        int id; char nome[50]; float preco;
                        printf("ID: "); scanf("%d", &id);
                        printf("Nome: "); scanf(" %[^\n]s", nome);
                        printf("Preco: "); scanf("%f", &preco);
                        cardapio = adicionarAoCardapio(cardapio, id, nome, preco);
                        pausar();

                    } else if (sub == 2) {
                        listarCardapio(cardapio);
                        pausar();
                    } else if (sub == 3) {
                        int id; printf("ID para editar: "); scanf("%d", &id);
                        editarItem(cardapio, id);
                        pausar();
                    } else if (sub == 4) {
                        int id; printf("ID para remover: "); scanf("%d", &id);
                        cardapio = deletarItem(cardapio, id);
                        pausar();
                    }
                } while (sub != 0);
                break;

            case 2:
                do {
                    system("clear || cls");
                    printf("--- GERENCIAR PEDIDOS ---\n");
                    printf("1. Novo Pedido\n");
                    printf("2. Ver Fila de Preparacao\n");
                    printf("3. Finalizar e Entregar\n");
                    printf("4. Cancelar Pedido Atual\n");
                    printf("5. Ver Pilha de Cancelados\n");
                    printf("0. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &sub);

                    if (sub == 1) {
                        int id; char cliente[50];
                        printf("ID Pedido: "); scanf("%d", &id);
                        printf("Nome Cliente: "); scanf(" %[^\n]s", cliente);
                        Pedido *p = criarPedido(id, cliente);
                        int id_i;
                        while(1) {
                            listarCardapio(cardapio);
                            printf("ID Item (0 para encerrar): "); scanf("%d", &id_i);
                            if(id_i == 0) break;
                            adicionarItemAoPedido(p, id_i);
                        }
                        enfileirarPedido(&fila, p);
                        pausar();
                    } else if (sub == 2) {
                        listarFilaPedidos(&fila);
                        pausar();
                    } else if (sub == 3) {
                        Pedido *entregue = desenfileirarPedido(&fila);
                        if(entregue) {
                            float valor;
                            printf("Total da venda para %s: ", entregue->nome_cliente); 
                            scanf("%f", &valor);
                            adicionarVenda(&fat, valor);
                            free(entregue->itens_id); 
                            free(entregue);
                        }
                        pausar();
                    } else if (sub == 4) {
                        if (fila.inicio != NULL) {
                            Pedido *c = desenfileirarPedido(&fila);
                            empilharCancelamento(&pilha, c);
                        } else printf("Fila vazia!\n");
                        pausar();
                    } else if (sub == 5) {
                        mostrarCancelamentos(&pilha);
                        pausar();
                    }
                } while (sub != 0);
                break;

            case 3:
                do {
                    system("clear || cls");
                    printf("--- FINANCEIRO ---\n");
                    printf("1. Relatorio de Vendas\n");
                    printf("0. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &sub);

                    if (sub == 1) {
                        mostrarRelatorio(&fat);
                        pausar();
                    }
                } while (sub != 0);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    } while (menu_principal != 0);

    return 0;
}