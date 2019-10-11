#ifndef TEST_H
#define TEST_H
#include <stdio.h>
#include "RBTree.h"
struct treenode * getparent(struct treenode *node) {
  return node->parent;
}

int insert(struct treehead *tree, int num) {
  struct treenode *node, *parent, *sibling, *grandparent, *newnode;
  newnode = malloc(sizeof(struct treenode));
  newnode->parent = NULL;
  newnode->left = NULL;
  newnode->right = NULL;
  newnode->color = red;
  

  // empty tree
  if (tree->count == 0) {
    tree->head = newnode;
    newnode->color = black;
    tree->count = 1;
    return 0;
  }
  
  node = tree->head;
  while (node != NULL) {
    if (node->key > num) {
      if (node->left == NULL) {
        node->left = newnode;
        break;
      }
      node = node->left;
    }
    else {
      if (node->right == NULL) {
        node->right == newnode;
        newnode->parent = node;
        tree->count++;
        balancer(newnode);
      }
      node = node->right;
    }
  }
  
}

int remove(struct treehead *tree, int num) {
  return 0;
}

#endif
