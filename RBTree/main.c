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
void printer(struct treehead * tree) {
    struct treenode *n = tree->head;
    printergo(n);
    printf("\n");
    fflush(stdout);
}


int main() {
    struct treehead * tree;
    tree = malloc(sizeof(struct treehead *));
    int i;
    for (i = 0; i < 10; i++) {
        insertnode(tree, i);    
        printer(tree);
    }
    printf("\n\nfinal tree: ");
    printer(tree);
    return 0;
}
