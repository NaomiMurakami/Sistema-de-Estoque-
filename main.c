#include <stdio.h>
#include "produto.h"
#include "categoria.h"

int main(void) {
  int opcao;
  int totalProdutos = 0;

  struct Produto produtos[MAX_PRODUTOS];
  
  /*variáveis da categoria*/
  int totalCategorias = 0;
  
  struct Categoria categorias[MAX_CATEGORIAS];

  do {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Pesquisar Produto\n");
    printf("4 - Categorias\n");
    printf("5 - Remover Produto\n");
    printf("6 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);

    if (opcao == 1) {
      totalProdutos = cadastrarProduto(produtos, totalProdutos, categorias, totalCategorias); /* regra 4 - deixar as listas de produtos e categorias independentes */
    } else if (opcao == 2) {
      listarProdutos(produtos, totalProdutos);
    } else if (opcao == 3) {
      pesquisarProduto(produtos, totalProdutos);
	} else if (opcao == 4) {
   
   int opcaoCategoria;
   do {
   	 printf("\n===== Categorias =====\n");
   	 printf("1 - Cadastrar Categoria\n");
   	 printf("2 - Listar Categoria\n");
   	 printf("3 - Excluir Categoria\n");
   	 printf("4 - Voltar\n");
   	 printf("Escolha uma opcao: ");
   	 
	scanf("%d", &opcaoCategoria);
	
	if (opcaoCategoria == 1) {
		totalCategorias = cadastrarCategoria(categorias, totalCategorias);
	} else if (opcaoCategoria == 2) {
		listarCategorias(categorias, totalCategorias);
	} else if (opcaoCategoria == 3) {
		totalCategorias = excluirCategoria(categorias, totalCategorias);
	} else if (opcaoCategoria == 4) {
		printf("Voltando para o menu principal\n");
	} else {
		printf("\nOpcao invalida! Tente novamente.\n");
	}
	} while (opcaoCategoria != 4);
	
	} else if (opcao == 5) {
		totalProdutos = excluirProduto(produtos, totalProdutos);
	
    } else if (opcao == 6) {
      printf("\nEncerrando o sistema...\n");
    } else {
      printf("\nOpcao invalida! Tente novamente.\n");
    }
  } while (opcao != 6);

  return 0;
}
