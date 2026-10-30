#include <stdio.h>
#include "produto.h"
#include "categoria.h"

int main(void) {
    int opcao;
    int totalProdutos = 0;
    int totalCategorias = 0;
    struct Produto produtos[MAX_PRODUTOS];
    struct Categoria categorias[MAX_CATEGORIAS];

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Alterar Estoque de um Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Categorias\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            totalProdutos = cadastrarProduto(produtos, totalProdutos, categorias, totalCategorias);
        } else if (opcao == 2) {
            listarProdutos(produtos, totalProdutos);
        } else if (opcao == 3) {
            pesquisarProduto(produtos, totalProdutos);
        } else if (opcao == 4) {
            alterarEstoque(produtos, totalProdutos);
        } else if (opcao == 5) {
            totalProdutos = excluirProduto(produtos, totalProdutos);
        } else if (opcao == 6) {
            int opcaoCategoria;
            do {
                printf("\n===== CATEGORIAS =====\n");
                printf("1 - Cadastrar Categoria\n");
                printf("2 - Listar Categorias\n");
                printf("3 - Voltar\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoCategoria);

                if (opcaoCategoria == 1) {
                    totalCategorias = cadastrarCategoria(categorias, totalCategorias);
                } else if (opcaoCategoria == 2) {
                    listarCategorias(categorias, totalCategorias);
                } else if (opcaoCategoria == 3) {
                    printf("Voltando para o menu principal...\n");
                } else {
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while (opcaoCategoria != 3);
        } else if (opcao == 7) {
            printf("\nEncerrando o sistema...\n");
        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
