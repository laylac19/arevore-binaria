#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar uma nova árvore vazia.
Tree *criar_arvore() {
  // Aloca memória para uma nova estrutura de árvore.
  Tree *arvore = (Tree *)malloc(sizeof(Tree));

  // Verifica se a alocação de memória foi bem-sucedida.
  if (arvore) {
    // Inicializa o ponteiro da raiz da árvore como nulo, indicando uma árvore vazia.
    arvore->raiz = NULL;
  }

  // Retorna a árvore recém-criada (pode ser nula se a alocação falhar).
  return arvore;
}


// Função para criar um novo nó com a chave fornecida.
TreeNode *criar_no(int chave) {
  // Aloca memória para um novo nó.
  TreeNode *no = (TreeNode *)malloc(sizeof(TreeNode));

  // Verifica se a alocação de memória foi bem-sucedida.
  if (no) {
    // Define a chave do nó com o valor fornecido.
    no->chave = chave;

    // Inicializa os ponteiros pai, esquerda e direita como nulos,
    // indicando que este é um novo nó sem pai ou filhos.
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
  }

  // Retorna o novo nó recém-criado (pode ser nulo se a alocação falhar).
  return no;
}


// Função para inserir um novo nó com a chave fornecida na árvore.
void inserir(Tree *arvore, int chave) {
  // Cria um novo nó com a chave fornecida.
  TreeNode *novo_no = criar_no(chave);

  // Verifica se a alocação de memória para o novo nó foi bem-sucedida.
  if (!novo_no) {
    printf("Erro ao alocar memoria para o no.\n");
    return;
  }

  // Inicializa os ponteiros pai, atual e pai do nó a ser inserido.
  TreeNode *pai = NULL;
  TreeNode *atual = arvore->raiz;

  // Percorre a árvore até encontrar a posição correta para inserir o novo nó.
  while (atual) {
    pai = atual;
    if (chave < atual->chave) {
      atual = atual->esq; // Move para a subárvore esquerda.
    } else {
      atual = atual->dir; // Move para a subárvore direita.
    }
  }

  // Define o pai do novo nó.
  novo_no->pai = pai;

  if (!pai) {
    // Se o pai for nulo, a árvore estava vazia, torna o novo nó a raiz.
    arvore->raiz = novo_no;
  } else if (chave < pai->chave) {
    pai->esq = novo_no; // Insere o novo nó como filho esquerdo.
  } else {
    pai->dir = novo_no; // Insere o novo nó como filho direito.
  }
}

// Função para buscar um nó com a chave fornecida na árvore.
TreeNode *buscar(Tree *arvore, int chave) {
  // Inicializa um ponteiro 'atual' com a raiz da árvore.
  TreeNode *atual = arvore->raiz;

  // Percorre a árvore até encontrar o nó com a chave correspondente ou até não haver mais nós a percorrer.
  while (atual) {
    if (chave == atual->chave) {
      return atual; // Retorna o nó se a chave for encontrada.
    } else if (chave < atual->chave) {
      atual = atual->esq; // Move para a subárvore esquerda se a chave for menor.
    } else {
      atual = atual->dir; // Move para a subárvore direita se a chave for maior.
    }
  }

  return NULL; // Retorna nulo se a chave não for encontrada na árvore.
}


// Função para encontrar o nó com o menor valor na subárvore a partir de um nó dado.
TreeNode *encontrar_minimo(TreeNode *no) {
  // Enquanto houver um filho à esquerda, percorre a árvore para encontrar o menor valor.
  while (no->esq) {
    no = no->esq;
  }
  return no; // Retorna o nó com o menor valor encontrado.
}

// Função para remover um nó com a chave fornecida da árvore.
void remover(Tree *arvore, int chave) {
  // Busca o nó com a chave a ser removida.
  TreeNode *no = buscar(arvore, chave);

  if (!no) {
    printf("Chave %d nao encontrada na arvore.\n", chave);
    return;
  }

  if (!no->esq) {
    // Se o nó não tem filho à esquerda, substitui-o pelo filho à direita (ou nulo).
    transplantar(arvore, no, no->dir);
  } else if (!no->dir) {
    // Se o nó não tem filho à direita, substitui-o pelo filho à esquerda (que não é nulo).
    transplantar(arvore, no, no->esq);
  } else {
    // Se o nó tem ambos os filhos, encontra o sucessor (menor valor maior que o nó) na subárvore direita.
    TreeNode *sucessor = encontrar_minimo(no->dir);

    if (sucessor->pai != no) {
      // Se o sucessor não é o filho direito imediato do nó, substitui o sucessor pelo seu filho direito (ou nulo).
      transplantar(arvore, sucessor, sucessor->dir);
      sucessor->dir = no->dir;
      sucessor->dir->pai = sucessor;
    }

    // Substitui o nó a ser removido pelo seu sucessor.
    transplantar(arvore, no, sucessor);
    sucessor->esq = no->esq;
    sucessor->esq->pai = sucessor;
  }

  // Libera a memória do nó removido.
  free(no);
}

// Função para substituir um nó da árvore por outro nó.
void transplantar(Tree *arvore, TreeNode *alvo, TreeNode *novo_no) {
  if (!alvo->pai) {
    // Se o nó a ser substituído é a raiz da árvore, atualiza a raiz para o novo nó.
    arvore->raiz = novo_no;
  } else if (alvo == alvo->pai->esq) {
    // Se o nó a ser substituído é o filho esquerdo do seu pai, atualiza o pai para apontar para o novo nó.
    alvo->pai->esq = novo_no;
  } else {
    // Se o nó a ser substituído é o filho direito do seu pai, atualiza o pai para apontar para o novo nó.
    alvo->pai->dir = novo_no;
  }

  if (novo_no) {
    // Se o novo nó existe, atualiza o pai do novo nó para apontar para o pai do nó a ser substituído.
    novo_no->pai = alvo->pai;
  }
}

// Função para verificar se a árvore está vazia.
void validarArvore(TreeNode *no) {
  if (no == NULL) {
    printf("\nArvore vazia.\n");
    return;
  }
}

// Função para imprimir os nós da árvore em ordem (in-order traversal).
void imprimir_em_ordem(TreeNode *no) {
  if (no) {
    // Recursivamente, primeiro imprime a subárvore esquerda, depois imprime a subárvore direita
    imprimir_em_ordem(no->esq);
    printf("%d ", no->chave);
    imprimir_em_ordem(no->dir);
  }
}

// Função para imprimir os nós da árvore em pré-ordem (pre-order traversal).
void imprimir_pre_ordem(TreeNode *no) {
  if (no) {
    // Imprime o próprio nó antes de percorrer as subárvores.
    printf("%d ", no->chave);
    // Recursivamente, visita a subárvore esquerda, depois a direita
    imprimir_pre_ordem(no->esq);
    imprimir_pre_ordem(no->dir);
  }
}

void imprimir_pos_ordem(TreeNode *no) {
  // Função para imprimir os nós da árvore em pós-ordem (post-order traversal).
  if (no) {
    // Recursivamente, visita a subárvore esquerda, depois a da direita
    imprimir_pos_ordem(no->esq);
    imprimir_pos_ordem(no->dir);
    printf("%d ", no->chave);
  }
}

// Função que exibe um menu interativo para operações em uma árvore binária de busca.
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
      inserir(*arvore, valor); // Insere um valor na árvore.
      break;
    case 2:
      printf("\nDigite o valor a ser removido: ");
      int valor_remover;
      scanf("%d", &valor_remover);
      remover(*arvore, valor_remover); // Remove um valor da árvore.
      break;
    case 3:
      printf("\nDigite o valor a ser buscado: ");
      int valor_buscar;
      scanf("%d", &valor_buscar);
      TreeNode *busca = buscar(*arvore, valor_buscar); // Busca um valor na árvore.
      validarArvore((*arvore)->raiz);
      imprimirResultadoBusca(busca, valor_buscar); // Exibe o resultado da busca.
      break;
    case 4:
      printf("\n\n---------- Arvore em ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_em_ordem((*arvore)->raiz); // Exibe a árvore em ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 5:
      printf("\n\n---------- Arvore em PRE-ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_pre_ordem((*arvore)->raiz); // Exibe a árvore em pré-ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 6:
      printf("\n\n---------- Arvore em POS-ORDEM ----------\n");
      validarArvore((*arvore)->raiz);
      imprimir_pos_ordem((*arvore)->raiz); // Exibe a árvore em pós-ordem.
      printf("\n-----------------------------------------\n\n");
      break;
    case 0:
      printf("Saindo do programa.\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  } while (opcao != 0);
}

// Função para imprimir o menu de opções interativas.
void imprimir_menu() {
  printf("\n---------- * MENU * ----------\n");
  printf("\t1. Inserir\n");               // Opção para inserir um valor na árvore.
  printf("\t2. Remover\n");               // Opção para remover um valor da árvore.
  printf("\t3. Buscar\n");                // Opção para buscar um valor na árvore.
  printf("\t4. Imprimir em ordem\n");     // Opção para imprimir a árvore em ordem.
  printf("\t5. Imprimir pre-ordem\n");    // Opção para imprimir a árvore em pré-ordem.
  printf("\t6. Imprimir pos-ordem\n");    // Opção para imprimir a árvore em pós-ordem.
  printf("\t0. Sair\n\n");                // Opção para sair do programa.
  printf("Escolha uma opção: ");          // Solicitação para que o usuário escolha uma opção.
}

// Função para imprimir o resultado de uma busca em uma árvore binária de busca.
void imprimirResultadoBusca(TreeNode *no, int valor_buscar) {
  if (no) {
    // Se o nó for não nulo, a chave foi encontrada na árvore.
    printf("\n\tChave %d - ENCONTRADA.\n", valor_buscar);
  } else {
    // Se o nó for nulo, a chave não foi encontrada na árvore.
    printf("\n\tChave %d - NAO ENCONTRADA\n", valor_buscar);
  }
}

