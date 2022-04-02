#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 100
void error_handling(char *message);

// 将参数二文件内容复制到参数三
int main(int argc, char** argv) {
    if (argc != 3) {
        error_handling("wants 3 arguments");
    }
    FILE *fp;
    char buf[BUF_SIZE];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        error_handling("fopen() error!");
    fgets(buf, BUF_SIZE, fp);
    fclose(fp);

    fp = fopen(argv[2], "w");
    if (fp == NULL)
        error_handling("fopen() error!");
    fputs(buf, fp);
    fclose(fp);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}