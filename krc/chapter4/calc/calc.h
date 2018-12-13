#ifndef CALC_H
#define CALC_H

#define NUMBER '0'	//标示找到一个数
double atof_pro(char s[]);
int getop(char s[]);
int getch(void);
void ungetch(int c);//将字符压回输入缓冲中
void push(double f);
double pop(void);
#define MAXVAL 100	//栈stack的最大深度

#endif
