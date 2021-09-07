
int f()
{
    static int x = 1;
    return x;
}

int g()
{
    static int x;
    return x;
}
