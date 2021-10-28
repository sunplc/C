
// 编译选项  gcc -S -O1 3.61.c

long cread_alt(long *xp)
{
    long eval = *xp;
    long rval = 0;
    int cond = xp != 0;
    if (cond) rval = eval;
    return rval;
}
