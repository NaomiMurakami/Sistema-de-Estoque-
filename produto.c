#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "util.h"
#include "categoria.h"

/* Exibe os dados  de um produto */
void exibirProduto(struct Produto produto) {
  printf("\n--- Dados do Produto ---\n");
  printf("Codigo: %d\n", produto.codigo);
  printf("Nome: %s\n", produto.nome);
  printf("Prateleira: %c\n", produto.prateleira);
  printf("Preco unitario: R$ %.2f\n", produto.precoUnitario);
  printf("Quantidade em estoque: %d\n", produto.quantidadeEstoque);

  if (produto.disponivelParaVenda == 1) {
    printf("Disponivel para venda: Sim\n");
  } else {
    printf("Disponivel para venda: Nao\n");
  }

  printf("------------------------\n");
}

/* Busca produto pelo codigo */
int buscarPorCodigo(struct Produto produtos[], int total, int codigo) {
  int i;

  for (i = 0; i < total; i++) {
    if (produtos[i].codigo == codigo) {
      return i;
    }
  }

  return -1;
}

/* Busca produto pelo nome */
int buscarPorNome(struct Produto produtos[], int total, char nome[]) {
  int i;

  for (i = 0; i < total; i++) {
    if (strcmp(produtos[i].nome, nome) == 0) {
      return i;
    }
  }

  return -1;
}

/* Excluir produto sem afetar a categoria */
int excluirProduto(struct Produto produtos[], int totalProdutos) {
	int codigo, i, posicao = -1;
	
	if (totalProdutos == 0) {
		printf("\nNenhum produto cadastrado para excluir.\n");
		return totalProdutos;
	}
	
	printf("\nDigite o codigo do produto que deseja excluir:");
	scanf("%d", &codigo);
	
	/* Procura a posição do produto pelo seu código */
    for (i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("Erro: Produto com o codigo %d nao encontrado!\n", codigo);
        return totalProdutos;
    }	
	
	/* Desloca os elementos seguintes para preencher o espaço do produto apagado */
    for (i = posicao; i < totalProdutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    
    printf("Produto excluido com sucesso!\n");
    printf("Nota: As categorias continuam totalmente inalteradas e seguras.\n");
    
    /* Retorna o total atualizado de produtos decrementado (-1) */
    return totalProdutos - 1; 
}


/* Cadastra um produto com validação de categorias (Regras 1 e 3) */
int cadastrarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias) {
  int codigoValido;
  int codigoCategoria;
  int posCategoria;

  /* Regra 3: Se não houver categorias, bloqueia o cadastro */
  if (totalCategorias == 0) {
    printf("\nErro: Nenhuma categoria cadastrada!\n");
    printf("Cadastre ao menos uma categoria antes de tentar cadastrar um produto.\n");
    return totalProdutos;
  }

  if (totalProdutos >= MAX_PRODUTOS) {
    printf("\nA lista de produtos esta cheia!\n");
    printf("Nao e possivel cadastrar mais produtos.\n");
    return totalProdutos;
  }

  printf("\n--- Cadastro de Produto ---\n");

  /* Regra 1: Validar se a categoria informada existe */
  listarCategorias(categorias, totalCategorias);
  
  do {
    printf("\nDigite o codigo da categoria do produto: ");
    scanf("%d", &codigoCategoria);

    posCategoria = buscarCategoriaPorCodigo(categorias, totalCategorias, codigoCategoria);
    if (posCategoria == -1) {
      printf("Erro: A categoria com o codigo %d nao existe! Tente novamente.\n", codigoCategoria);
    }
  } while (posCategoria == -1);

  /* Guarda a categoria associada ao produto */
  produtos[totalProdutos].codigoCategoria = codigoCategoria;

  /* Codigo do produto: positivo e único */
  do {
    codigoValido = 1;

    printf("Codigo do produto: ");
    scanf("%d", &produtos[totalProdutos].codigo);

    if (!validarInteiroPositivo(produtos[totalProdutos].codigo)) {
      printf("O codigo deve ser um numero positivo!\n");
      codigoValido = 0;
    } else if (buscarPorCodigo(produtos, totalProdutos, produtos[totalProdutos].codigo) != -1) {
      printf("Esse codigo ja esta cadastrado!\n");
      codigoValido = 0;
    }

  } while (!codigoValido);

  /* Nome */
  do {
    printf("Nome do produto: ");
    scanf(" %49[^\n]", produtos[totalProdutos].nome);

    if (!validarTextoPreenchido(produtos[totalProdutos].nome)) {
      printf("O nome nao pode ficar em branco!\n");
    }

  } while (!validarTextoPreenchido(produtos[totalProdutos].nome));

  /* Prateleira */
  do {
    printf("Prateleira (A, B, C ou D): ");
    scanf(" %c", &produtos[totalProdutos].prateleira);

    if (!validarCaractereEm(produtos[totalProdutos].prateleira, "ABCD")) {
      printf("Prateleira invalida! Use apenas A, B, C ou D.\n");
    }

  } while (!validarCaractereEm(produtos[totalProdutos].prateleira, "ABCD"));

  /* Preco: maior que zero */
  do {
    printf("Preco unitario: ");
    scanf("%f", &produtos[totalProdutos].precoUnitario);

    if (!validarFloatPositivo(produtos[totalProdutos].precoUnitario)) {
      printf("O preco deve ser maior que zero!\n");
    }

  } while (!validarFloatPositivo(produtos[totalProdutos].precoUnitario));

  /* Quantidade: aceita zero */
  do {
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[totalProdutos].quantidadeEstoque);

    if (!validarInteiroNaoNegativo(produtos[totalProdutos].quantidadeEstoque)) {
      printf("A quantidade nao pode ser negativa!\n");
    }

  } while (!validarInteiroNaoNegativo(produtos[totalProdutos].quantidadeEstoque));

  /* Disponibilidade calculada automaticamente */
  if (produtos[totalProdutos].quantidadeEstoque > 0) {
    produtos[totalProdutos].disponivelParaVenda = 1;
  } else {
    produtos[totalProdutos].disponivelParaVenda = 0;
  }

  /* Exibe resumo */
  printf("\n--- Resumo do Produto Cadastrado ---\n");
  exibirProduto(produtos[totalProdutos]);

  return totalProdutos + 1;
}

/* Lista todos os produtos */
void listarProdutos(struct Produto produtos[], int total) {
  int i;

  if (total == 0) {
    printf("\nNenhum produto foi cadastrado.\n");
    return;
  }

  printf("\n===== LISTA DE PRODUTOS =====\n");

  for (i = 0; i < total; i++) {
    exibirProduto(produtos[i]);
  }
}

/* Pesquisa um produto */
void pesquisarProduto(struct Produto produtos[], int total) {
  int opcaoPesquisa;
  int codigo;
  int posicao;
  char nome[50];

  if (total == 0) {
    printf("\nNenhum produto foi cadastrado.\n");
    return;
  }

  printf("\n===== PESQUISAR PRODUTO =====\n");
  printf("1 - Por codigo\n");
  printf("2 - Por nome\n");
  printf("Escolha uma opcao: ");
  scanf("%d", &opcaoPesquisa);

  if (opcaoPesquisa == 1) {

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    posicao = buscarPorCodigo(produtos, total, codigo);

    if (posicao != -1) {
      exibirProduto(produtos[posicao]);
    } else {
      printf("\nNenhum produto foi encontrado.\n");
    }

  } else if (opcaoPesquisa == 2) {

    printf("Digite o nome do produto: ");
    scanf(" %49[^\n]", nome);

    posicao = buscarPorNome(produtos, total, nome);

    if (posicao != -1) {
      exibirProduto(produtos[posicao]);
    } else {
      printf("\nNenhum produto foi encontrado.\n");
    }

  } else {
    printf("\nOpcao de pesquisa invalida!\n");
  }
}
