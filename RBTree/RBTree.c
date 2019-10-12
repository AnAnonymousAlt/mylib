#include "RBTree.h"

struct treehead * head;

struct treenode * getparent(struct treenode *node) {
  return node->parent;
}
struct treenode * getsibling(struct treenode *node) {
  if (node->parent == NULL) {
    return NULL;
  }
  if (node->parent->left == node) {
    return node->parent->right;
  }
  else return node->parent->left;
}
//struct treenode *
enum rbcolor getcolor(struct treenode *node) {
  return node == NULL ? black : node->color;
}

// balance tree after insertion
// tree head case not include
int insertbalancer (struct treenode *node) {
  if (getparent(node) == NULL) {
    if (getcolor(node) == red) {
      node->color = black;
      return 0;
    }
  }

  if (getparent(node)->color == black) {
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
    if (parent->parent == NULL) {
      head->head = parent;
    }
    else {
      if (parent->parent->left == grandparent) {
        parent->parent->left = parent;
      }
      else {
        parent->parent->right = parent;
      }
    }
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
    if (node->parent == NULL) {
      head->head = node;
    }
    else {
      if (node->parent->left == grandparent) {
        node->parent->left = node;
      }
      else {
        node->parent->right = node;
      }
    }
    return 0;
  }
  else if (grandparent->right == parent && parent->right == node) {
    parent->color = black;
    grandparent->color = red;
    grandparent->right = parent->left;
    parent->left = grandparent;
    parent->parent = grandparent->parent;
    grandparent->parent = parent;
    if (parent->parent == NULL) {
      head->head = parent;
    }
    else {
      if (parent->parent->left == grandparent) {
        parent->parent->left = parent;
      }
      else {
        parent->parent->right = parent;
      }
    }
    return 0;
  }
  else if (grandparent->right == parent && parent->left == node) {
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
    if (node->parent == NULL) {
      head->head = node;
    }
    else {
      if (node->parent->left == grandparent) {
        node->parent->left = node;
      }
      else {
        node->parent->right = node;
      }
    }
    return 0;
  }
  else {
    return 1;
  }
}

int insertnode(struct treehead *tree, int num) {
  head = tree;
  struct treenode *node, *parent, *sibling, *grandparent, *newnode;
  newnode = malloc(sizeof(struct treenode));
  newnode->parent = NULL;
  newnode->left = NULL;
  newnode->right = NULL;
  newnode->color = red;
  newnode->key = num;
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
        node->right = newnode;
        newnode->parent = node;
        tree->count++;
        return insertbalancer(newnode);
      }
      node = node->right;
    }
  }
  
}

struct treenode * searchnode(struct treehead *tree, int num) {
  if (tree == NULL) {
    return NULL;
  }
  struct treenode * node = tree->head;
  if (node == NULL) {
    return NULL;
  }
  while (node != NULL) {
    if (node->key == num) {
      return node;
    }
    else if (node->key > num) {
      if (node->left != NULL) {
        node = node->left;
      }
      else {
        return NULL;
      }
    }
    else {
      if (node->key < num) {
        if (node->right != NULL) {
          node = node->right;
        }
        else {
          return NULL;
        }
      }
    }
  }
  return NULL;
}

int deletenode(struct treehead *tree, int num) {
  head = tree;
  struct treenode *node, *subnode, *left, *right;
  struct treenode *parent, *sibling, *nephew;
  if ((node = searchnode(tree, num)) == NULL) {
    return 1;
  }
  // head case
  if (tree->head == node) {
    tree->count--;
    tree->head = NULL;
    free(node);
    return 0;
  }
  if (node->right != NULL) {
    subnode = node->right;
    while(subnode->left != NULL) {
      subnode = subnode->left;
    }
    node->key = subnode->key;
  }
  else if (node->left != NULL) {
    subnode = node->left;
    while(subnode->right != NULL) {
      subnode = subnode->right;
    }
    node->key = subnode->key;
  }
  else {
    subnode = node;
  }
  // delete subnode, ignore node
  node = subnode;
  if (node->left != NULL) {
    subnode = node->left;
  }
  else {
    subnode = node->right;
  }
  // simple case: either is red
  if (getcolor(subnode) != getcolor(node)) {
    // Parent of node
    if (subnode != NULL) {
      subnode->parent = node->parent; 
    }
    if ((parent = getparent(node)) != NULL) {
      if (parent->left == node) {
        parent->left = subnode;
      }
      else {
        parent->right = subnode;
      }
      node->parent = NULL;
    }
    // no parent: head case
    else {
      head->head = subnode;
    }
    node->left = NULL;
    node->right = NULL;
    free(node);
    return 0;
  }

  // double black
  
  // db case 1: sibling has red child
  doubleblack(node);

  return 0;
}
void doubleblack(struct treenode *node) {
  struct treenode *sibling, *parent, *nephew;
  sibling = getsibling(node);
  parent = getparent(node);
  if (node->left == node->right && node->left == NULL) {
    if (parent->left == node) {
      parent->left = NULL;
      node->parent = NULL;
      free(node);
    }
  }
  if (getcolor(sibling->right) == red) {
    if (sibling->parent->right == sibling) {
      sibling->parent = parent->parent;
      parent->parent = sibling;
      parent->right = sibling->left;
      sibling->left = parent;
      sibling->right->color = black;
    }
  }
  else if (getcolor(sibling->left) == red) {
    if (sibling->parent->right == sibling) {
      nephew = sibling->left;
      sibling->color = red;
      nephew->color = black;
      nephew->parent = parent;
      nephew->right = sibling;
      sibling->parent = nephew;
      sibling->left = NULL;
    }
  }
}
