#ifndef TEST_H
#define TEST_H
#include <stdio.h>
#include "RBTree.h"
struct treenode * getparent(struct treenode *node) {
  return node->parent;
}
struct treenode * getsibling(struct treenode *node) {
  if (node->parent->left == node) {
    return node->parent->right;
  }
  else return node->parent->left;
}
//struct treenode *
enum rbcolor getcolor(struct treenode *node) {
  return node->color;
}

// balance tree after insertion
// tree head case not include
int insertbalancer (struct treenode *node) {
  if (getparent(node) == NULL || getparent(node)->color == black) {
    return 0;
  }

  struct treenode *parent, *uncle, *grandparent, *sibling;
  parent = getparent(node);
  grandparent = getparent(parent);
  uncle = getsibling(parent);
  sibling = getsibling(node);

  if(uncle != NULL && getcolor(uncle) == red) {
    uncle->color = black;
    parent->color = black;
    grandparent->color = red;
    return insertbalancer (grandparent);
  }

  // four cases
  if (parent->left == node && grandparent->left == parent) {
    parent->color = black;
    grandparent->color = red;
    grandparent->left = parent->right;
    parent->right = grandparent;
    // change parent
    parent->parent = grandparent->parent;
    grandparent->parent = parent;
    return 0;
  }
  else if (grandparent->left == parent && parent->right == node) {
    parent->right = node->left;
    node->left = parent;
    parent->parent = node;
    node->parent = grandparent;
    // LL
    node->color = black;
    grandparent->color = red;
    grandparent->left = node->right;
    node->right = grandparent;
    node->parent = grandparent->parent;
    grandparent->parent = node;
    return 0;
  }
  else if (grandparent->right == parent && parent->right == newnode) {
    parent->color = black;
    grandparent->color = red;
    grandparent->right = parent->left;
    parent->left = grandparent;
    parent->parent = grandparent->parent;
    grandparent->parent = parent;
    return 0;
  }
  else if (grandparent->right == parent && parent->left == newnode) {
    parent->left = node->right;
    node->right = parent;
    parent->parent = node;
    node->parent = grandparent;
    // RR
    node->color = black;
    grandparent->color = red;
    grandparent->right = node->left;
    node->left = grandparent;
    node->parent = grandparent->parent;
    grandparent->parent = node;
    return 0;
  }
  else {
    return 1;
  }
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
        newnode->parent = node;
        tree->count++;
        return insertbalancer(newnode);
      }
      node = node->left;
    }
    else {
      if (node->right == NULL) {
        node->right == newnode;
        newnode->parent = node;
        tree->count++;
        return insertbalancer(newnode);
      }
      node = node->right;
    }
  }
  
}

int remove(struct treehead *tree, int num) {
  return 0;
}

#endif
