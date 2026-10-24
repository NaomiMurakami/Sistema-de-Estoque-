#include <stdio.h>
#include <string.h>
#include "categoria.h"

/* funçao para procurar a categoria pelo código, retorna o indice se encontrar e  -1 se náo encontrar / regra 1 - impossivel cadastrar um produto em uma categoria que nao faz parte da lista */
int buscarCategoriaPorCodigo(struct Categoria categorias[], int totalCategorias, int codigo) {
	int i;
	for (i = 0; i < totalCategorias; i++) {
		if (categorias[i].codigo == codigo) {
			return i; 
		}
	}
	return -1;
}
int cadastrarCategoria(struct Categoria categorias[], int totalCategorias) {
	int codigo;
    if (totalCategorias >= MAX_CATEGORIAS) {
        printf("\nLimite de categorias atingido!\n");
        return totalCategorias;
    }
    
    printf("\n===== CADASTRO DE CATEGORIA =====\n");
    printf("Digite o codigo da categoria: ");
    scanf("%d", &codigo);
    
    /* regra 2 - nao pode repetir o codigo igual acontece com o produto */
    if (buscarCategoriaPorCodigo(categorias, totalCategorias, codigo) != -1) {
        printf("\nErro: Ja existe uma categoria cadastrada com o codigo %d!\n", codigo);
        return totalCategorias; // Cancela o cadastro sem alterar o total
    }
    
    categorias[totalCategorias].codigo = codigo;
    
    printf("Digite o nome da categoria: ");
    scanf(" %[^\n]", categorias[totalCategorias].nome);
    
    printf("\nCategoria cadastrada com sucesso!\n");
    
    return totalCategorias + 1;
}

void listarCategorias(struct Categoria categorias[], int totalCategorias) {
    int i;
    
    printf("\n===== LISTA DE CATEGORIAS =====\n");
    
    if (totalCategorias == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }
    
    for (i = 0; i < totalCategorias; i++) {
        printf("Codigo: %d | Nome: %s\n", categorias[i].codigo, categorias[i].nome);
    }
}

int excluirCategoria(struct Categoria categorias[], int totalCategorias) {
    int codigo, i, posicao = -1;
    
    if (totalCategorias == 0) {
        printf("\nNenhuma categoria cadastrada para excluir.\n");
        return totalCategorias;
    }
    
    printf("\nDigite o codigo da categoria que deseja excluir: ");
    scanf("%d", &codigo);
    
    /* Procura a posição da categoria pelo código */
    for (i = 0; i < totalCategorias; i++) {
        if (categorias[i].codigo == codigo) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("Erro: Categoria com o codigo %d nao encontrada!\n", codigo);
        return totalCategorias;
    }
    
    /* Desloca os elementos seguintes para preencher o espaço */
    for (i = posicao; i < totalCategorias - 1; i++) {
        categorias[i] = categorias[i + 1];
    }
    
    printf("Categoria excluida com sucesso!\n");
    printf("Nota: Os produtos cadastrados continuam na sua propria lista.\n");
    
    return totalCategorias - 1;
}
