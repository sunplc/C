#include <stdio.h>
#include <string.h>

typedef struct
{
    int year, month, day;
} date_t;

typedef struct
{
    char name[16];
    date_t birthday;
    char address[100];
    char tel[12];
} contact_t;

int main(int argc, char *argv[])
{
    contact_t contacts[10] = {
        {"海明威", {1999, 3, 4}, "北京市朝阳区", "13512121212"},
        {"卡夫卡", {1880, 3, 6}, "奥地利布拉格", "10321234"},
        {"鲁迅", {1881, 10, 12}, "浙江省绍兴市", "234123"}
    };

    printf("%ld\n", sizeof(date_t));
    int len = sizeof(contacts) / sizeof(contacts[0]);
    int i;
    for (i = 0; i < len; i++) {
        if (strlen(contacts[i].name) > 0)
        printf("%s %d-%d-%d %s %s\n",
            contacts[i].name, contacts[i].birthday.year,
            contacts[i].birthday.month, contacts[i].birthday.day,
            contacts[i].address, contacts[i].tel);
    }

	return 0;
}

