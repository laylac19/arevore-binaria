#include "tree.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    Tree* arvore;
    arvore = criar_arvore(); // Cria uma arvore vazia
    menu(&arvore); // Inicia o menu interativo para manipular a árvore

    return 0;
}

