#include "RBTree.h"

struct treeroot * tree;

struct treenode * getparent(struct treenode *node) {
  return node->parent;
}
struct treenode * getleftchild(struct treenode *node) {
  return node->left;
}
struct treenode * getrightchild(struct treenode * node) {
  return node->right;
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
struct treenode * getroot(void) {
  return gettree()->root;
}
struct treeroot gettree(void) {
  return tree;
}
int gettreecount() {
  return gettree()->count;
}
enum rbcolor getcolor(struct treenode *node) {
  return node == NULL ? black : node->color;
}

bool isleftchild(struct treenode *node, struct treenode *parent) {
  return (getleftchild(parent) == node);
}
bool isleaf(struct treenode *node) {
  return (node->key == -1);
}

int setcolor(struct treenode *node, enum rbcolor color) {
  node->color = color;
  return 0;
}
int setleftchild(struct treenode *node, struct treenode *parent) {
  parent->left = node;
  node->parent = parent;
  return 0;
}
int setrightchild(struct treenode *node, struct treenode *parent) {
  parent->right = node;
  node->parent = parent;
  return 0;
}
int setparent(struct treenode *node, struct treenode *parent) {
  node->parent = parent;
  return 0;
}
int setleftparent(struct treenode *node, struct treenode *parent) {
  setparent(node, parent);
  setleftchild(node, parent);
  return 0;
}
int setrightparent(struct treenode *node, struct treenode *parent) {
  setparent(node, parent);
  setrightchild(node, parent);
  return 0;
}
int setkey(struct treenode *node, int key) {
  node->key = key;
  return 0;
}
int setroot(struct treenode *node) {
  root->root = node;
  return 0;
}
int settreecount(int count) {
  gettree()->count = count;
  return 0;
}

int storetree(struct treeroot *_tree) {
  tree = _tree;
  return 0;
}
int restoretree(void) {
  tree = NULL;
  return 0;
}

int leftrotate(struct treenode *node, struct treenode *subnode) {
  setrightparent(getleftchild(subnode), node);
  if (getparent(node)) {
    isleftchild(node, getparent(node)) 
      ? setleftparent(subnode, getparent(node)) 
      : setrightparent(subnode, getparent(node));
  }
  setleftparent(node, subnode);
  return 0;
}

int rightrotate(struct treenode *node, struct treenode * subnode) {
  setleftparent(getrightchild(subnode), node);
  if (getparent(node)) {
    isleftchild(node, getparent(node))
      ? setleftparent(subnode, getparent(node))
      : setrightparent(subnode, getparent(node));
  }
  setrightparent(node, subnode);
  return 0;
}

struct treenode * newemptynode() {
  struct treenode * node = malloc(sizeof(struct treenode));
  setparent(node, NULL);
  setleftchild(NULL, node);
  setrightchild(NULL, node);
  setkey(node, -1);
  setcolor(node, black);
  return node;
}
struct treenode * newnode(int key) {
  struct treenode *node, *left, *right;
  node = newemptynode();
  left = newemptynode();
  right = newemptynode();
  setkey(node, key);
  setcolor(node, red);
  setleftparent(left, node);
  setrightparent(right, node);
  return node;
}

// balance tree after insertion
// tree root case not include
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
      root->root = parent;
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
      root->root = node;
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
      root->root = parent;
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
      root->root = node;
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

int insertnode(struct treeroot *tree, int key) {
  storetree(tree);
  struct treenode *node, *parent, *sibling, *grandparent;
  
  // empty tree
  if (!gettreecount()) {
    node = newnode(key);
    setroot(node);
    setcolor(node, black);
    settreecount(gettreecount() + 1);
    return 0;
  }
  
  node = getroot();
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

struct treenode * searchnode(struct treeroot *tree, int num) {
  if (tree == NULL) {
    return NULL;
  }
  struct treenode * node = tree->root;
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

int deletenode(struct treeroot *tree, int num) {
  root = tree;
  struct treenode *node, *subnode, *left, *right;
  struct treenode *parent, *sibling, *nephew;
  if ((node = searchnode(tree, num)) == NULL) {
    return 1;
  }
  // root case
  if (tree->root == node) {
    tree->count--;
    tree->root = NULL;
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
    // no parent: root case
    else {
      root->root = subnode;
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
