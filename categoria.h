#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 100

struct Categoria {
	int codigo;
	char nome [50];
};

/*decalaracao das funcoes da categoria*/
int buscarCategoriasPorCodigo(struct Categoria categorias[], int totalCategorias, int codigo);
int cadastrarCategoria(struct Categoria categorias[], int totalCategorias);
void listarCategorias(struct Categoria categorias[], int totalCategorias);

#endif
