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
struct treenode * getsibling(struct treenode *);
struct treenode * getleftchild(struct treenode *);
struct treenode * getrightchild(struct treenode *);
enum rbcolor getcolor(struct treenode *);

int setcolor(struct treenode *, enum rbcolor);
int setleftchild(struct treenode *, struct treenode *);
int setrightchild(struct treenode *, struct treenode *);
int setleftparent(struct treenode *, struct treenode *);
int setrightparent(struct treenode *, struct treenode *);
int setparent(struct treenode *, struct treenode *);
int setkey(struct treenode *, int );

struct treenode * newnode(int);
int storehead(struct treehead *);
int restorehead(void);

int insertnode(struct treehead *, int);
int deletenode(struct treehead *, int);

int insertbalancer(struct treenode *);
void doubleblack(struct treenode *);
int leftrotate(struct treenode *, struct treenode *);
int rightrotate(struct treenode *, struct treenode *);
#endif