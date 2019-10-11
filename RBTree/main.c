#include <stdio.h>
int main() {
    enum a {h,b};
    enum a k = b;
    printf("%d\n", k);
    return 0;
}