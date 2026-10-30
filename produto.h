#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50

struct Produto {
    int codigo;
    char nome[50];
    char prateleira;
    float precoUnitario;
    int quantidadeEstoque;
    int disponivelParaVenda;
    int codigoCategoria;
    int ativo;
};

void exibirProduto(struct Produto produto);
int cadastrarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias);
int buscarPorCodigo(struct Produto produtos[], int total, int codigo);
int buscarPorNome(struct Produto produtos[], int total, char nome[]);
void listarProdutos(struct Produto produtos[], int total);
void pesquisarProduto(struct Produto produtos[], int total);
void alterarEstoque(struct Produto produtos[], int totalProdutos);
int excluirProduto(struct Produto produtos[], int totalProdutos);

#endif
