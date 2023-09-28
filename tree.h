#ifndef TREE_H
#define TREE_H

// Defini��o da estrutura de um n� da �rvore bin�ria de busca.
typedef struct tipoNo {
    int chave;             // Chave do n�.
    struct tipoNo* pai;    // Ponteiro para o n� pai.
    struct tipoNo* esq;    // Ponteiro para o n� filho esquerdo.
    struct tipoNo* dir;    // Ponteiro para o n� filho direito.
} TreeNode;

// Defini��o da estrutura da �rvore bin�ria de busca.
typedef struct {
    TreeNode* raiz;        // Ponteiro para a raiz da �rvore.
} Tree;

// Prot�tipos das fun��es dispon�veis.

Tree* criar_arvore();                                    // Cria uma nova �rvore.
TreeNode *criar_no(int chave);                          // Cria um novo n� com a chave especificada.
void inserir(Tree* arvore, int chave);                   // Insere um n� na �rvore.
TreeNode* buscar(Tree* arvore, int chave);               // Busca um n� com a chave especificada.
TreeNode *encontrar_minimo(TreeNode *no);               // Encontra o n� com a menor chave na sub�rvore.
void remover(Tree* arvore, int chave);                  // Remove um n� com a chave especificada da �rvore.
void imprimir_pre_ordem(TreeNode* no);                   // Imprime os n�s em pr�-ordem.
void imprimir_em_ordem(TreeNode* no);                   // Imprime os n�s em ordem.
void imprimir_pos_ordem(TreeNode* no);                   // Imprime os n�s em p�s-ordem.
void transplantar(Tree* arvore, TreeNode* alvo, TreeNode* novo_no); // Transplanta um n�.
void menu(Tree** arvore);                                // Exibe um menu interativo para o usu�rio.
void imprimir_menu();                                    // Imprime o menu de op��es.
void validarArvore(TreeNode *no);                        // Valida se a �rvore est� vazia.
void imprimirResultadoBusca(TreeNode* no, int valor_buscar); // Imprime o resultado de uma busca.

#endif

