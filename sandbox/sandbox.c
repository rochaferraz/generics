#include "tt.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int x = 0;
    int y = 1;
    printf("x is %d and y is %d\n", x, y);
    _swap(&x, &y, sizeof(int));
    printf("x is %d and y is %d\n", x, y);
    swap_int(&x, &y);
    printf("x is %d and y is %d\n", x, y);
    return 0;
}