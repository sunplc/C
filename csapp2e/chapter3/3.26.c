/*
 * Answer of question B:
 * function arith return (x + 3) / 4 when x is
 * negative, or return x /4 when x is not 
 * negative
 */
#include <stdio.h>

#define OP >= 0 ? x / 4 : (x + 3) / 


int arith(int x) {
    return x OP 4;
}

int main() {
    printf("%d\n", arith(21));
}

