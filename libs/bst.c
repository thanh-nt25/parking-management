#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BST: Bin Search Tree
#include "bst.h"

// tro den du lieu muon so sanh nao thi da -> trong data_t.c roi
tree_t search(keyT x, tree_t root) {
  data_t* k = &(root->data);
  if (root == NULL)
    return NULL;
  else if (eq(x, k))  
    return root;
  else if (gt(x, k))  
    return search(x, root->right);
  else {
    return search(x, root->left);
  }
}
 
void insertNode(data_t x, tree_t *pRoot) {
  if (*pRoot == NULL) {
    *pRoot = (node_bst_t *)malloc(sizeof(node_bst_t));
    (*pRoot)->data = x;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (lt(x.bien_so, &((*pRoot)->data)))  // THAY ĐỔI TRƯỜNG SO SÁNH
    insertNode(x, &((*pRoot)->left));
  else if (gt(x.bien_so, &((*pRoot)->data)))  // THAY ĐỔI TRƯỜNG SO SÁNH
    insertNode(x, &((*pRoot)->right));
}

// xóa phần tử có key nhỏ nhất
data_t deleteMin(tree_t *root) {
  if ((*root)->left == NULL) {
    data_t k = (*root)->data;
    (*root) = (*root)->right;
    return k;
  } else
    return deleteMin(&(*root)->left);
}

// xóa node theo key
// void deleteNode(keyT x, tree_t *root) {
//   if (*root != NULL)
//     if (lt(x, &((*root)->data)))
//       deleteNode(x, &(*root)->left);
//     else if (gt(x, &((*root)->data)))
//       deleteNode(x, &(*root)->right);
//     else if (((*root)->left == NULL) && ((*root)->right == NULL))
//       *root = NULL;
//     else if ((*root)->left == NULL)
//       *root = (*root)->right;
//     else if ((*root)->right == NULL)
//       *root = (*root)->left;
//     else
//       (*root)->data = deleteMin(&(*root)->right);
// }

void prettyPrint(tree_t tree) {
  static char prefix[200] = "    ";
  char *prefixend = prefix + strlen(prefix);
  if (tree != NULL) {
    showData(tree->data);
    if (tree->left != NULL)
      if (tree->right == NULL) {
        printf("\304");
        strcat(prefix, "     ");
      } else {
        printf("\302");
        strcat(prefix, "\263    ");
      }
    prettyPrint(tree->left);
    *prefixend = '\0';
    if (tree->right != NULL)
      if (tree->left != NULL) {
        printf("\n%s", prefix);
        printf("\300");
      } else
        printf("\304");
    strcat(prefix, "     ");
    prettyPrint(tree->right);
  }
}

void freeTree(tree_t tree) {
  if (tree != NULL) {
    freeTree(tree->left);
    freeTree(tree->right);
    free((void *)tree);
  }
}

