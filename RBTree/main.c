#include "RBTree.h"

// printer
void printergo(struct treenode *n) {
    if (n->left != NULL) {
        printergo(n->left);
    }
    printf("%d\t", n->key);
    if (n->right != NULL) {
        printergo(n->right);
    }
}
void printer(struct treeroot * tree) {
    struct treenode *n = tree->root;
    printergo(n);
    printf("\n");
    fflush(stdout);
}


int main() {
    struct treeroot * tree;
    tree = malloc(sizeof(struct treeroot *));
    int i;
    for (i = 5; i < 10; i++) {
        insertnode(tree, i);    
        printer(tree);
    }
    for (i = 0; i < 5; i++) {
        insertnode(tree, i);    
        printer(tree);
    }
    printf("\n\nfinal tree: \t");
    printer(tree);
    return 0;
}
