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
};d