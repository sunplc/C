
int absdiff(int x, int y) {
    return x < y ? y - x : x - y;
}

int cmovdiff(int x, int y) {
    int tval = y - x;
    int rval = x - y;
    int test = x < y;
    /* Line below requires 
        single instruction: */
    if (test) rval = tval;

    return rval;
}
