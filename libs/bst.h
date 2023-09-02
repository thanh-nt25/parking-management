#ifndef __BST_H__
#define __BST_H__

// --- Declaration ------------------------------------------------------------
#include "data_t.h"

typedef struct node_bst_s {
  data_t data;
  struct node_bst_s *left;
  struct node_bst_s *right;
} node_bst_t;

typedef node_bst_t *tree_t;

// --- BST --------------------------------------------------------------------

tree_t search(keyT x, tree_t root);
void insertNode(data_t x, tree_t *pRoot);
data_t deleteMin(tree_t *pRoot);
void deleteNode(keyT x, tree_t *pRoot);
void prettyPrint(tree_t tree);
void freeTree(tree_t tree);

void iter_inorder(tree_t node);

#endif