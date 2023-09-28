#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// Fun��o para criar uma nova �rvore vazia.
Tree *criar_arvore() {
  // Aloca mem�ria para uma nova estrutura de �rvore.
  Tree *arvore = (Tree *)malloc(sizeof(Tree));

  // Verifica se a aloca��o de mem�ria foi bem-sucedida.
  if (arvore) {
    // Inicializa o ponteiro da raiz da �rvore como nulo, indicando uma �rvore vazia.
    arvore->raiz = NULL;
  }

  // Retorna a �rvore rec�m-criada (pode ser nula se a aloca��o falhar).
  return arvore;
}


// Fun��o para criar um novo n� com a chave fornecida.
TreeNode *criar_no(int chave) {
  // Aloca mem�ria para um novo n�.
  TreeNode *no = (TreeNode *)malloc(sizeof(TreeNode));

  // Verifica se a aloca��o de mem�ria foi bem-sucedida.
  if (no) {
    // Define a chave do n� com o valor fornecido.
    no->chave = chave;

    // Inicializa os ponteiros pai, esquerda e direita como nulos,
    // indicando que este � um novo n� sem pai ou filhos.
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
  }

  // Retorna o novo n� rec�m-criado (pode ser nulo se a aloca��o falhar).
  return no;
}


// Fun��o para inserir um novo n� com a chave fornecida na �rvore.
void inserir(Tree *arvore, int chave) {
  // Cria um novo n� com a chave fornecida.
  TreeNode *novo_no = criar_no(chave);

  // Verifica se a aloca��o de mem�ria para o novo n� foi bem-sucedida.
  if (!novo_no) {
    printf("Erro ao alocar memoria para o no.\n");
    return;
  }

  // Inicializa os ponteiros pai, atual e pai do n� a ser inserido.
  TreeNode *pai = NULL;
  TreeNode *atual = arvore->raiz;

  // Percorre a �rvore at� encontrar a posi��o correta para inserir o novo n�.
  while (atual) {
    pai = atual;
    if (chave < atual->chave) {
      atual = atual->esq; // Move para a sub�rvore esquerda.
    } else {
      atual = atual->dir; // Move para a sub�rvore direita.
    }
  }

  // Define o pai do novo n�.
  novo_no->pai = pai;

  if (!pai) {
    // Se o pai for nulo, a �rvore estava vazia, torna o novo n� a raiz.
    arvore->raiz = novo_no;
  } else if (chave < pai->chave) {
    pai->esq = novo_no; // Insere o novo n� como filho esquerdo.
  } else {
    pai->dir = novo_no; // Insere o novo n� como filho direito.
  }
}

// Fun��o para buscar um n� com a chave fornecida na �rvore.
TreeNode *buscar(Tree *arvore, int chave) {
  // Inicializa um ponteiro 'atual' com a raiz da �rvore.
  TreeNode *atual = arvore->raiz;

  // Percorre a �rvore at� encontrar o n� com a chave correspondente ou at� n�o haver mais n�s a percorrer.
  while (atual) {
    if (chave == atual->chave) {
      return atual; // Retorna o n� se a chave for encontrada.
    } else if (chave < atual->chave) {
      atual = atual->esq; // Move para a sub�rvore esquerda se a chave for menor.
    } else {
      atual = atual->dir; // Move para a sub�rvore direita se a chave for maior.
    }
  }

  return NULL; // Retorna nulo se a chave n�o for encontrada na �rvore.
}


// Fun��o para encontrar o n� com o menor valor na sub�rvore a partir de um n� dado.
TreeNode *encontrar_minimo(TreeNode *no) {
  // Enquanto houver um filho � esquerda, percorre a �rvore para encontrar o menor valor.
  while (no->esq) {
    no = no->esq;
  }
  return no; // Retorna o n� com o menor valor encontrado.
}

// Fun��o para remover um n� com a chave fornecida da �rvore.
void remover(Tree *arvore, int chave) {
  // Busca o n� com a chave a ser removida.
  TreeNode *no = buscar(arvore, chave);

  if (!no) {
    printf("Chave %d nao encontrada na arvore.\n", chave);
    return;
  }

  if (!no->esq) {
    // Se o n� n�o tem filho � esquerda, substitui-o pelo filho � direita (ou nulo).
    transplantar(arvore, no, no->dir);
  } else if (!no->dir) {
    // Se o n� n�o tem filho � direita, substitui-o pelo filho � esquerda (que n�o � nulo).
    transplantar(arvore, no, no->esq);
  } else {
    // Se o n� tem ambos os filhos, encontra o sucessor (menor valor maior que o n�) na sub�rvore direita.
    TreeNode *sucessor = encontrar_minimo(no->dir);

    if (sucessor->pai != no) {
      // Se o sucessor n�o � o filho direito imediato do n�, substitui o sucessor pelo seu filho direito (ou nulo).
      transplantar(arvore, sucessor, sucessor->dir);
      sucessor->dir = no->dir;
      sucessor->dir->pai = sucessor;
    }

    // Substitui o n� a ser removido pelo seu sucessor.
    transplantar(arvore, no, sucessor);
    sucessor->esq = no->esq;
    sucessor->esq->pai = sucessor;
  }

  // Libera a mem�ria do n� removido.
  free(no);
}

// Fun��o para substituir um n� da �rvore por outro n�.
void transplantar(Tree *arvore, TreeNode *alvo, TreeNode *novo_no) {
  if (!alvo->pai) {
    // Se o n� a ser substitu�do � a raiz da �rvore, atualiza a raiz para o novo n�.
    arvore->raiz = novo_no;
  } else if (alvo == alvo->pai->esq) {
    // Se o n� a ser substitu�do � o filho esquerdo do seu pai, atualiza o pai para apontar para o novo n�.
    alvo->pai->esq = novo_no;
  } else {
    // Se o n� a ser substitu�do � o filho direito do seu pai, atualiza o pai para apontar para o novo n�.
    alvo->pai->dir = novo_no;
  }

  if (novo_no) {
    // Se o novo n� existe, atualiza o pai do novo n� para apontar para o pai do n� a ser substitu�do.
    novo_no->pai = alvo->pai;
  }
}

// Fun��o para verificar se a �rvore est� vazia.
void validarArvore(TreeNode *no) {
  if (no == NULL) {
    printf("\nArvore vazia.\n");
    return;
  }
}

// Fun��o para imprimir os n�s da �rvore em ordem (in-order traversal).
void imprimir_em_ordem(TreeNode *no) {
  if (no) {
    // Recursivamente, primeiro imprime a sub�rvore esquerda, depois imprime a sub�rvore direita
    imprimir_em_ordem(no->esq);
    printf("%d ", no->chave);
    imprimir_em_ordem(no->dir);
  }
}

// Fun��o para imprimir os n�s da �rvore em pr�-ordem (pre-order traversal).
void imprimir_pre_ordem(TreeNode *no) {
  if (no) {
    // Imprime o pr�prio n� antes de percorrer as sub�rvores.
    printf("%d ", no->chave);
    // Recursivamente, visita a sub�rvore esquerda, depois a direita
    imprimir_pre_ordem(no->esq);
    imprimir_pre_ordem(no->dir);
  }
}

void imprimir_pos_ordem(TreeNode *no) {
  // Fun��o para imprimir os n�s da �rvore em p�s-ordem (post-order traversal).
  if (no) {
    // Recursivamente, visita a sub�rvore esquerda, depois a da direita
    imprimir_pos_ordem(no->esq);
    imprimir_pos_ordem(no->dir);
    printf("%d ", no->chave);
  }
}

// Fun��o que exibe um menu interativo para opera��es em uma �rvore bin�ria de busca.
void menu(Tree **arvore) {
  int opcao;
  do {
    imprimir_menu();
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\nDigite o valor a ser inserido: ");
      int valor;
      scanf("%d", &valor);
      inserir(*arvore, valor); // Insere um valor na �rvore.
      break;
    case 2:
      printf("\nDigite o valor a ser removido: ");
      int valor_remover;
      scanf("%d", &valor_remover);
      remover(*arvore, valor_remover); // Remove um valor da �rvore.
      break;
    case 3:
      printf("\nDigite o valor a ser buscado: ");
      int valor_buscar;
      scanf("%d", &valor_buscar);
      TreeNode *busca = buscar(*arvore, valor_buscar); // Busca um valor na �rvore.
      validarArvore((*arvore)->raiz);
      imprimirResultadoBusca(busca, valor_buscar); // Exibe o resultado da busca.
      break;
    case 4:
      printf("\n\n---------- Arvore em ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_em_ordem((*arvore)->raiz); // Exibe a �rvore em ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 5:
      printf("\n\n---------- Arvore em PRE-ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_pre_ordem((*arvore)->raiz); // Exibe a �rvore em pr�-ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 6:
      printf("\n\n---------- Arvore em POS-ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_pos_ordem((*arvore)->raiz); // Exibe a �rvore em p�s-ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 0:
      printf("Saindo do programa.\n");
      break;
    default:
      printf("Op��o inv�lida. Tente novamente.\n");
      break;
    }
  } while (opcao != 0);
}

// Fun��o para imprimir o menu de op��es interativas.
void imprimir_menu() {
  printf("\n---------- * MENU * ----------\n");
  printf("\t1. Inserir\n");               // Op��o para inserir um valor na �rvore.
  printf("\t2. Remover\n");               // Op��o para remover um valor da �rvore.
  printf("\t3. Buscar\n");                // Op��o para buscar um valor na �rvore.
  printf("\t4. Imprimir em ordem\n");     // Op��o para imprimir a �rvore em ordem.
  printf("\t5. Imprimir pre-ordem\n");    // Op��o para imprimir a �rvore em pr�-ordem.
  printf("\t6. Imprimir pos-ordem\n");    // Op��o para imprimir a �rvore em p�s-ordem.
  printf("\t0. Sair\n\n");                // Op��o para sair do programa.
  printf("Escolha uma op��o: ");          // Solicita��o para que o usu�rio escolha uma op��o.
}

// Fun��o para imprimir o resultado de uma busca em uma �rvore bin�ria de busca.
void imprimirResultadoBusca(TreeNode *no, int valor_buscar) {
  if (no) {
    // Se o n� for n�o nulo, a chave foi encontrada na �rvore.
    printf("\n\tChave %d - ENCONTRADA.\n", valor_buscar);
  } else {
    // Se o n� for nulo, a chave n�o foi encontrada na �rvore.
    printf("\n\tChave %d - NAO ENCONTRADA\n", valor_buscar);
  }
}

