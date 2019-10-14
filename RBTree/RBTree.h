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
struct treeroot {
  struct treenode *root;
  int count;
};

struct treenode * getparent(struct treenode *);
struct treenode * getsibling(struct treenode *);
struct treenode * getleftchild(struct treenode *);
struct treenode * getrightchild(struct treenode *);
struct treenode * getroot(void);
struct treeroot * gettree()
int gettreecount();
enum rbcolor getcolor(struct treenode *);

int setcolor(struct treenode *, enum rbcolor);
int setleftchild(struct treenode *, struct treenode *);
int setrightchild(struct treenode *, struct treenode *);
int setleftparent(struct treenode *, struct treenode *);
int setrightparent(struct treenode *, struct treenode *);
int setparent(struct treenode *, struct treenode *);
int setkey(struct treenode *, int );
int setroot(struct treenode *);
int settreecount(int);

bool isleftchild(struct treenode *, struct treenode *);
bool isleaf(struct treenode *);

struct treenode * newnode(int);
int storetree(struct treeroot *);
int restoretree(void);

int insertnode(struct treeroot *, int);
int deletenode(struct treeroot *, int);

int insertbalancer(struct treenode *);
void doubleblack(struct treenode *);
int leftrotate(struct treenode *, struct treenode *);
int rightrotate(struct treenode *, struct treenode *);
#endif