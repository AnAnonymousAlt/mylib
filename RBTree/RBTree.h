enum rbcolor {red, black};
struct node {
  struct node *parent;
  struct node *left;
  struct node *right;
  enum rbcolor color;
  int key;
}
struct treehead {
  struct node *head;
  int count;
}