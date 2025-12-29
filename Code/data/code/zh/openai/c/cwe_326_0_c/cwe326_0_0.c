#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // 密钥长度
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d", key_length);
    
    // 使用管道执行命令并读取输出
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 返回 NULL 表示发生错误
    }

    // 读取生成的 PEM 密钥
    char *pem_key = NULL;
    size_t key_size = 0;
    size_t read_size;
    char buffer[1024];

    while ((read_size = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        char *temp = realloc(pem_key, key_size + read_size + 1);
        if (temp == NULL) {
            free(pem_key);
            pclose(fp);
            return NULL; // 返回 NULL 表示发生错误
        }
        pem_key = temp;

        memcpy(pem_key + key_size, buffer, read_size);
        key_size += read_size;
        pem_key[key_size] = '\0'; // 终止字符串
    }

    pclose(fp);
    return pem_key; // 返回生成的 PEM 格式 RSA 私有密钥
}