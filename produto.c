#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "util.h"
#include "categoria.h"

/* Exibe os dados de um produto ativo. */
void exibirProduto(struct Produto produto) {
    printf("\n--- Dados do Produto ---\n");
    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco unitario: R$ %.2f\n", produto.precoUnitario);
    printf("Quantidade em estoque: %d\n", produto.quantidadeEstoque);
    printf("Disponivel para venda: %s\n", produto.disponivelParaVenda == 1 ? "Sim" : "Nao");
    printf("------------------------\n");
}

/* As buscas consideram somente produtos ativos. */
int buscarPorCodigo(struct Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1 && produtos[i].codigo == codigo) return i;
    }
    return -1;
}

int buscarPorNome(struct Produto produtos[], int total, char nome[]) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1 && strcmp(produtos[i].nome, nome) == 0) return i;
    }
    return -1;
}

int cadastrarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias) {
    int codigoValido, codigoCategoria, posCategoria, i;

    if (totalCategorias == 0) {
        printf("\nErro: Nenhuma categoria cadastrada!\nCadastre ao menos uma categoria antes de cadastrar um produto.\n");
        return totalProdutos;
    }
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\nA lista de produtos esta cheia!\n");
        return totalProdutos;
    }

    printf("\n--- Cadastro de Produto ---\n");
    listarCategorias(categorias, totalCategorias);
    do {
        printf("\nDigite o codigo da categoria do produto: ");
        scanf("%d", &codigoCategoria);
        posCategoria = buscarCategoriaPorCodigo(categorias, totalCategorias, codigoCategoria);
        if (posCategoria == -1) printf("Erro: Categoria nao encontrada! Tente novamente.\n");
    } while (posCategoria == -1);
    produtos[totalProdutos].codigoCategoria = codigoCategoria;

    do {
        codigoValido = 1;
        printf("Codigo do produto: ");
        scanf("%d", &produtos[totalProdutos].codigo);
        if (!validarInteiroPositivo(produtos[totalProdutos].codigo)) {
            printf("O codigo deve ser positivo!\n");
            codigoValido = 0;
        } else {
            /* Mantem codigos unicos inclusive entre produtos inativos. */
            for (i = 0; i < totalProdutos; i++) {
                if (produtos[i].codigo == produtos[totalProdutos].codigo) {
                    printf("Esse codigo ja foi utilizado!\n");
                    codigoValido = 0;
                    break;
                }
            }
        }
    } while (!codigoValido);

    do {
        printf("Nome do produto: ");
        scanf(" %49[^\n]", produtos[totalProdutos].nome);
        if (!validarTextoPreenchido(produtos[totalProdutos].nome)) printf("O nome nao pode ficar em branco!\n");
    } while (!validarTextoPreenchido(produtos[totalProdutos].nome));

    do {
        printf("Prateleira (A, B, C ou D): ");
        scanf(" %c", &produtos[totalProdutos].prateleira);
        if (!validarCaractereEm(produtos[totalProdutos].prateleira, "ABCD")) printf("Prateleira invalida! Use A, B, C ou D.\n");
    } while (!validarCaractereEm(produtos[totalProdutos].prateleira, "ABCD"));

    do {
        printf("Preco unitario: ");
        scanf("%f", &produtos[totalProdutos].precoUnitario);
        if (!validarFloatPositivo(produtos[totalProdutos].precoUnitario)) printf("O preco deve ser maior que zero!\n");
    } while (!validarFloatPositivo(produtos[totalProdutos].precoUnitario));

    do {
        printf("Quantidade em estoque: ");
        scanf("%d", &produtos[totalProdutos].quantidadeEstoque);
        if (!validarInteiroNaoNegativo(produtos[totalProdutos].quantidadeEstoque)) printf("A quantidade nao pode ser negativa!\n");
    } while (!validarInteiroNaoNegativo(produtos[totalProdutos].quantidadeEstoque));

    produtos[totalProdutos].disponivelParaVenda = produtos[totalProdutos].quantidadeEstoque > 0 ? 1 : 0;
    produtos[totalProdutos].ativo = 1;

    printf("\n--- Resumo do Produto Cadastrado ---\n");
    exibirProduto(produtos[totalProdutos]);
    return totalProdutos + 1;
}

void listarProdutos(struct Produto produtos[], int total) {
    int i, encontrados = 0;
    printf("\n===== LISTA DE PRODUTOS =====\n");
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1) {
            exibirProduto(produtos[i]);
            encontrados++;
        }
    }
    if (encontrados == 0) printf("Nenhum produto ativo cadastrado.\n");
}

void pesquisarProduto(struct Produto produtos[], int total) {
    int opcaoPesquisa, codigo, posicao;
    char nome[50];

    printf("\n===== PESQUISAR PRODUTO =====\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoPesquisa);

    if (opcaoPesquisa == 1) {
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);
        posicao = buscarPorCodigo(produtos, total, codigo);
    } else if (opcaoPesquisa == 2) {
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]", nome);
        posicao = buscarPorNome(produtos, total, nome);
    } else {
        printf("\nOpcao de pesquisa invalida!\n");
        return;
    }

    if (posicao != -1) exibirProduto(produtos[posicao]);
    else printf("\nNenhum produto ativo foi encontrado.\n");
}

void alterarEstoque(struct Produto produtos[], int totalProdutos) {
    int codigo, posicao, tipo, quantidade;

    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    posicao = buscarPorCodigo(produtos, totalProdutos, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado ou inativo!\n");
        return;
    }

    printf("1 - Entrada de mercadoria\n");
    printf("2 - Saida de mercadoria\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &tipo);
    if (tipo != 1 && tipo != 2) {
        printf("Opcao invalida! Estoque nao alterado.\n");
        return;
    }

    do {
        printf("Quantidade: ");
        scanf("%d", &quantidade);
        if (!validarInteiroPositivo(quantidade)) printf("Digite uma quantidade maior que zero!\n");
    } while (!validarInteiroPositivo(quantidade));

    if (tipo == 1) {
        produtos[posicao].quantidadeEstoque += quantidade;
    } else {
        if (quantidade > produtos[posicao].quantidadeEstoque) {
            printf("Estoque insuficiente! Operacao cancelada. Estoque atual: %d\n", produtos[posicao].quantidadeEstoque);
            return;
        }
        produtos[posicao].quantidadeEstoque -= quantidade;
    }

    produtos[posicao].disponivelParaVenda = produtos[posicao].quantidadeEstoque > 0 ? 1 : 0;
    printf("Estoque atualizado com sucesso!\n");
    exibirProduto(produtos[posicao]);
}

/* Exclusao logica: o registro permanece na mesma posicao da lista. */
int excluirProduto(struct Produto produtos[], int totalProdutos) {
    int codigo, posicao;
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado para remover.\n");
        return totalProdutos;
    }

    printf("\nDigite o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);
    posicao = buscarPorCodigo(produtos, totalProdutos, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado ou ja inativo!\n");
        return totalProdutos;
    }

    produtos[posicao].ativo = 0;
    printf("Produto removido com sucesso! O registro foi mantido como inativo.\n");
    printf("A categoria vinculada ao produto nao foi alterada.\n");
    return totalProdutos;
}
