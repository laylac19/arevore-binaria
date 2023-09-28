#ifndef TREE_H
#define TREE_H

// Definição da estrutura de um nó da árvore binária de busca.
typedef struct tipoNo {
    int chave;             // Chave do nó.
    struct tipoNo* pai;    // Ponteiro para o nó pai.
    struct tipoNo* esq;    // Ponteiro para o nó filho esquerdo.
    struct tipoNo* dir;    // Ponteiro para o nó filho direito.
} TreeNode;

// Definição da estrutura da árvore binária de busca.
typedef struct {
    TreeNode* raiz;        // Ponteiro para a raiz da árvore.
} Tree;

// Protótipos das funções disponíveis.

Tree* criar_arvore();                                    // Cria uma nova árvore.
TreeNode *criar_no(int chave);                          // Cria um novo nó com a chave especificada.
void inserir(Tree* arvore, int chave);                   // Insere um nó na árvore.
TreeNode* buscar(Tree* arvore, int chave);               // Busca um nó com a chave especificada.
TreeNode *encontrar_minimo(TreeNode *no);               // Encontra o nó com a menor chave na subárvore.
void remover(Tree* arvore, int chave);                  // Remove um nó com a chave especificada da árvore.
void imprimir_pre_ordem(TreeNode* no);                   // Imprime os nós em pré-ordem.
void imprimir_em_ordem(TreeNode* no);                   // Imprime os nós em ordem.
void imprimir_pos_ordem(TreeNode* no);                   // Imprime os nós em pós-ordem.
void transplantar(Tree* arvore, TreeNode* alvo, TreeNode* novo_no); // Transplanta um nó.
void menu(Tree** arvore);                                // Exibe um menu interativo para o usuário.
void imprimir_menu();                                    // Imprime o menu de opções.
void validarArvore(TreeNode *no);                        // Valida se a árvore está vazia.
void imprimirResultadoBusca(TreeNode* no, int valor_buscar); // Imprime o resultado de uma busca.

#endif

