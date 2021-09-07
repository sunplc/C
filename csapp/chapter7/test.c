
int g;

int *p = &g;

//void add()
//{
//    static int x;
//    x++;
//    g = x;
//}

void add(int, int);

int main()
{
    g++;
    add(g, g);

    return 0;
}
