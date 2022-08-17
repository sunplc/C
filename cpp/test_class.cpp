#include <stdio.h>
#include <string.h>

class CGirl
{
public:
    char m_name[50];
    int m_age;
    int m_height;
    char m_describe[30];
    int Show();
};

int CGirl::Show()
{
    printf("name: %s, age: %d, height: %d, describe: %s\n", m_name, m_age, m_height, m_describe);
    return 1;
}

int main()
{
    CGirl Girl;

    strcpy(Girl.m_name, "西施");
    Girl.m_age = 20;
    Girl.m_height = 170;
    strcpy(Girl.m_describe, "beautiful");

    Girl.Show();

    return 0;
}