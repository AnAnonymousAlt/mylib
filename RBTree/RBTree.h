enum rbcolor {red, black};
struct treenode {
  struct node *parent;
  struct node *left;
  struct node *right;
  enum rbcolor color;
  int key;
};
struct treehead {
  struct node *head;
  int count;
};

struct treenode * getparent(struct treenode *);
int insert(struct treehead *tree, int);
int remove(struct treehead *, int);
int insertbalancer(struct treenode *);
