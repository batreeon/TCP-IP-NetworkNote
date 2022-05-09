#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int i;
    struct hostent *host;
    if (argc != 2)
    {
        printf("Usage : %s <addr>\n", argv[0]);
        exit(1);
    }
    // 把参数传递给函数，返回结构体
    host = gethostbyname(argv[1]);
    if (!host)
        error_handling("gethost... error");
    // 输出官方域名
    printf("Official name: %s \n", host->h_name);
    // Aliases 貌似是解析的 cname 域名？
    for (i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]);
    //看看是不是ipv4
    printf("Address type: %s \n",
           (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    // 输出ip地址信息
    // host->h_addr_list[i]数组中的元素类型为 in_addr* 类型，但是结构体host中h_addr_list成员类型为char*
    // 因此先强制类型转换，然后用*取内容
    for (i = 0; host->h_addr_list[i]; i++)
        printf("IP addr %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}