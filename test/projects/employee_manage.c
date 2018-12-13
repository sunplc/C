/**
 * 雇员信息管理程序
 * 2018-07-22 supercilious
 *
 * 使用定长的结构体数组保存数据，程序退出时保存数据到 .dat 文件中
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RSDA_DATA_FILENAME "RSDA.dat"   //数据保存的文件名

#define HEADER1         "---------------------------------- records --------------------------------\n"
#define HEADER2         "|   id   |   name   |  jbgz  |   jj   |   kk   |  yfgz  |   sk   |  sfgz  |\n"
#define HEADER3         "|--------|----------|--------|--------|--------|--------|--------|--------|\n"
#define TABLE_END       "---------------------------------------------------------------------------\n"
#define FIELDS_FORMAT   "|%-8d|%-10s|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|\n"
#define RSDA_FIELDS     p->id, p->name, p->jbgz, p->jj, p->kk, p->yfgz, p->sk, p->sfgz

#define DATA_LEN 100    // 雇员数组的初始长度,也是最大长度

typedef struct employee
{
    int id;         // 职工编号
    char name[15];  // 职工姓名
    float jbgz;     // 基本工资
    float jj;       // 奖金
    float kk;       // 扣款
    float yfgz;     // 应发工资
    float sk;       // 税款
    float sfgz;     // 实发工资
} RSDA;

int data_len = DATA_LEN;
RSDA ems[DATA_LEN];

void menu(void)
{
    printf("           The Employee Management System             \n");
    printf("    ********************* Menu ********************** \n");
    printf("    *  1 input record             2 delete record   * \n");
    printf("    *  3 search record            4 modify record   * \n");
    printf("    *  5 insert record            6 count record    * \n");
    printf("    *  7 sort record              8 save record     * \n");
    printf("    *  9 display record           0 quit            * \n");
    printf("    ************************************************* \n");
}

/**
 * 输入提示语，并获取一个数字
 */
float number_input(char *notice)
{
    printf(notice);
    float f;
    scanf("%f", &f);
    return f;
}

/**
 * 输入提示语，并获取一个字符串
 */
void string_input(char *str, int len, char *notice)
{
    if (len <= 0 || len > 999) {
        printf("the len you specified is too long\n");
        exit(1);
    }
    printf(notice);
    char format[6];
    sprintf(format, "%%%ds", len);
    scanf(format, str);
    *(str + strlen(str)) = '\0';
}

/**
 * 打印记录集的表头
 */
void print_header(void)
{
    printf(HEADER1);
    printf(HEADER2);
    printf(HEADER3);
}

/**
 * 打印数据集的表尾
 */
void printf_end(void)
{
    printf(TABLE_END);
}

/**
 * 打印一行记录
 */
void display_record(RSDA ems[], int len)
{
    RSDA *p = ems;
    if (p == NULL || len < 1)
        return;

    print_header();
    while (len-- > 0) {
        printf(FIELDS_FORMAT, RSDA_FIELDS);
        if (len > 0)
            printf(HEADER3);
        ++p;
    }
    printf_end();
}

/**
 * 保存记录集到文件
 */
int save_records(RSDA ems[], int len)
{
    char *data_file = RSDA_DATA_FILENAME;
    FILE *fp = fopen(data_file, "w");
    if (fp == NULL) {
        printf("打开数据文件失败\n");
        return 0;
    }
    
    long node_len = sizeof(RSDA);

    fseek(fp, 0, SEEK_SET);
    int ret = 1;

    // fwrite 函数执行成功时返回写入的数据块个数，出错时返回0
    if (fwrite(ems, node_len, len, fp) <= 0) {
        ret = 0;
    }
    fclose(fp);

    return ret;
}

/**
 * 在指定记录之后插入一条记录
 */
int insert_record(RSDA ems[], int len)
{
    RSDA *p, *temp, *old_p;

    p = ems;
    old_p = p;

    int id , index = -1, max_index = 0, max_id = 0, i;

    id = number_input("请输入要插入在其后的雇员的id:\n");

    for (i = 0; i < len; i++) {

        if (p->id == id) {
            index = i; //要插入在其后的雇员的下标
            temp = p;
        }
        
        if (i > max_index)
            max_index = i;

        if (p->id > max_id)
            max_id = p->id;

        ++p;
    }

    // 该id的雇员未找到
    if (index == -1) {
        index = max_index;
        p = ems;
        temp = p + len - 1;
    }

    index += 1;

    printf("要插入在其后的雇员的信息： id=%d , name=%s\n", temp->id, temp->name);
    printf("目前最大id = %d\n", max_id);


    RSDA new;

    new.id = (int) number_input("请输入新雇员的id:\n");
    string_input(new.name, 15, "请输入新雇员的姓名:\n");
    // printf("strlen=%ld\n", strlen(new.name));

    char str[10];
    string_input(str, 10, "请输入新雇员的基本工资\n");
    new.jbgz = atof(str);
    string_input(str, 10, "请输入新雇员的奖金\n");
    new.jj = atof(str);
    string_input(str, 10, "请输入新雇员的扣款\n");
    new.kk = atof(str);
    string_input(str, 10, "请输入新雇员的应发工资\n");
    new.yfgz = atof(str);
    string_input(str, 10, "请输入新雇员的税款\n");
    new.sk = atof(str);
    string_input(str, 10, "请输入新雇员的实发工资\n");
    new.sfgz = atof(str);

    p = &new;
    printf(FIELDS_FORMAT, RSDA_FIELDS);
    p = old_p;


    // 将数组中要插入位置后面的元素都向后移动一位
    for (i = len; i > index; i--) {
        ems[i] = ems[i-1];
        // printf(">>> %d - %d\n", i, i+1);
    }
    // 将新元素插入 index 位置
    ems[index] = new;


    save_records(ems, len + 1);
    display_record(ems, len + 1);

    return len + 1;
}

/**
 * 修改指定记录
 */
int modify_record(RSDA ems[], int len)
{
    RSDA *p;
    p = ems;

    int id , index = -1, i;

    id = number_input("请输入修改的雇员的id:\n");

    for (i = 0; i < len; i++, ++p) {
        if (p->id == id) {
            index = i; //要插入在其后的雇员的下标
            break;
        }
    }

    // 该id的雇员未找到
    if (index == -1) {
        printf("找不到您要修改的雇员\n");
        return 0;

    } else {

        printf("index = %d, 要修改的雇员信息 ：\n", index);
        printf(FIELDS_FORMAT, RSDA_FIELDS);

        char option[1];
        string_input(option, 1, "是否继续修改？(y/n)");
        if (option[0] == 'n' || option[0] == 'N')
            return 1;   // 不修改
    }


    RSDA new;

    new.id = id;
    string_input(new.name, 15, "请输入雇员的姓名:\n");
    // printf("strlen=%ld\n", strlen(new.name));

    char str[10];
    string_input(str, 10, "请输入雇员的基本工资\n");
    new.jbgz = atof(str);
    string_input(str, 10, "请输入雇员的奖金\n");
    new.jj = atof(str);
    string_input(str, 10, "请输入雇员的扣款\n");
    new.kk = atof(str);
    string_input(str, 10, "请输入雇员的应发工资\n");
    new.yfgz = atof(str);
    string_input(str, 10, "请输入雇员的税款\n");
    new.sk = atof(str);
    string_input(str, 10, "请输入雇员的实发工资\n");
    new.sfgz = atof(str);

    p = &new;
    printf(FIELDS_FORMAT, RSDA_FIELDS);


    // 更新数组的 index 元素
    ems[index] = new;


    save_records(ems, len);
    display_record(ems, len);

    return len;
}

/**
 * 删除指定记录
 */
int delete_record(RSDA ems[], int len)
{
    RSDA *p;
    p = ems;


    int id , index = -1, i;

    id = number_input("请输入要删除的雇员的id:\n");

    for (i = 0; i < len; i++, ++p) {
        if (p->id == id) {
            index = i; //要插入在其后的雇员的下标
            break;
        }
    }

    if (index == -1) {
        printf("找不到您要删除的雇员id\n");
        return 0;

    } else {

        printf("index = %d, 要删除的雇员信息 ：\n", index);
        printf(FIELDS_FORMAT, RSDA_FIELDS);

        char option[1];
        string_input(option, 1, "是否确定删除？(y/n)");
        if (option[0] == 'n' || option[0] == 'N')
            return 1;   // 不删除
    }


    // 将数组中要删除元素位置后面的元素都向前移动一位
    for (i = index; i < len - 1; i++) {
        ems[i] = ems[i + 1];
    }


    save_records(ems, len - 1);
    display_record(ems, len - 1);

    return len - 1;
}

/**
 * 清除标准输入流的缓冲区，并清屏
 */
void Clear(void)
{
    // 一般从终端输入数字或字符串并用scanf读取之后，
    // 标准输入流缓冲中有一个换行符'\n'（按回车键产生的）没有被读取
    // 所以需要清除输入缓冲区
    
    // fflush(stdin); // only work in Windows platform
    
    // 清除输入缓冲，直到换行符或文件结束标识符
    int c;
    while ( (c = getchar()) != '\n' && c != EOF)
        ;

    //清屏
    system("clear");
}

int main(int argc, char *argv[])
{
    char *data_file = RSDA_DATA_FILENAME;
    FILE *fp = fopen(data_file, "ab+");
    if (fp == NULL) {
        printf("打开数据文件失败\n");
        return 0;
    }

    //RSDA em[5] = {
    //    {1, "小明", 2000, 1000, 300,  2700, 400, 2300},
    //    {2, "小强", 2000, 1000, 300,  2700, 400, 2300},
    //    {3, "小红", 2000, 1000, 300,  2700, 400, 2300},
    //    {4, "过客", 18000, 1000, 300,  2700, 400, 2300},
    //};
    //fwrite(em, sizeof(RSDA), 5, fp);

    fseek(fp, 0, SEEK_END);
    long pos = ftell(fp);
    long node_len = sizeof(RSDA);
    data_len = (int) pos / node_len;
    
    int i;
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < data_len; i++) {
        fread(&ems[i], node_len, 1, fp);
    }
    fclose(fp);


    char option[1];

    while (1) {
        menu();
        int number = number_input("Please enter your choice (0~9):");

        switch (number) {
            case 1:
            case 5:
                data_len = insert_record(ems, data_len);
                break;
            case 2:
                data_len = delete_record(ems, data_len);
                break;
            case 4:
                modify_record(ems, data_len);
                break;
            case 6:
                printf("count = %d\n", data_len);
                break;
            case 3:
            case 9:
                display_record(ems, data_len);
                break;
            case 0:
                return 0;
                break;
            default:
                printf("输入选项有错误，请重新输入\n");
        }
        
        string_input(option, 1, "是否继续运行本程序？(y/n)");
        if (option[0] == 'n' || option[0] == 'N')
            break;

        Clear();
    }

	return 0;
}
