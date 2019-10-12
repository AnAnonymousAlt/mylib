#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
enum rbcolor {red, black};
struct treenode {
  struct treenode *parent;
  struct treenode *left;
  struct treenode *right;
  enum rbcolor color;
  int key;
};
struct treehead {
  struct treenode *head;
  int count;
};

struct treenode * getparent(struct treenode *);
int insertnode(struct treehead *tree, int);
int deletenode(struct treehead *, int);
int insertbalancer(struct treenode *);
void doubleblack(struct treenode *);
#endif