#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

/* 取子串的函数 */
static char* substr(const char*str, unsigned start, unsigned end)
{
    unsigned n = end - start;
    static char stbuf[256];
    strncpy(stbuf, str + start, n);
    stbuf[n] = 0;
    return stbuf;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./test 192.168.1.100\n");
        exit(1);
    }
    char *input = argv[1];
    // 匹配邮箱的正则表达式
    char *pattern = "[0-9a-zA-Z_.-]+@[0-9a-zA-Z_.-]+\\.[0-9a-zA-Z_.-]+"; 
    // 匹配ip地址的正则表达式
    //char *pattern = "([0-9]{1,3}\\.){3}[0-9]{1,3}"; 
    
    regex_t reg;
    // REG_EXTENDED 正则表达式的扩展模式，
    // 基本模式（Basic）中，字符?+{}|()解释为普通字符
    int z = regcomp(&reg, pattern, REG_EXTENDED);
    char errbuf[128];
    // 如果出错
    if (z != 0) {
        regerror(z, &reg, errbuf, sizeof(errbuf));
        fprintf(stderr, "%s: pattern '%s' \n", errbuf, pattern);
        return 1;
    }

    if ((z = strlen(input)) > 0 && input[z-1] == '\n')
        input[z-1] = 0;

    const size_t nmatch = 10;
    regmatch_t pm[10];
    z = regexec(&reg, input, nmatch, pm, 0);
    //if (z == REG_NOMATCH)
        //continue;
    if (z != 0) {
        regerror(z, &reg, errbuf, sizeof(errbuf));
        fprintf(stderr, "%s: regcom('%s')\n", errbuf, input);
        return 2;
    }
    printf("z=%ld\n", nmatch);
    int x;
    /* 输出处理结果 */
    for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x) {
        printf("$%d='%s'\n", x, substr(input, pm[x].rm_so, pm[x].rm_eo));
    }
    //puts(input);
    regfree(&reg);
    return 0;
}

