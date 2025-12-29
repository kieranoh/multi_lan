#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048;  // 标准 RSA 密钥长度
    char command[256];
    FILE *fp;
    char *result = NULL;
    char buffer[4096];
    size_t total_size = 0;
    size_t bytes_read;
    
    // 构建 openssl 命令
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 执行命令并读取输出
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 读取命令输出
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        // 重新分配内存以容纳新数据
        char *temp = realloc(result, total_size + bytes_read + 1);
        if (temp == NULL) {
            free(result);
            pclose(fp);
            return NULL;
        }
        result = temp;
        
        // 复制新数据
        memcpy(result + total_size, buffer, bytes_read);
        total_size += bytes_read;
    }
    
    // 关闭管道
    int status = pclose(fp);
    
    // 检查命令是否成功执行
    if (status != 0 || total_size == 0) {
        free(result);
        return NULL;
    }
    
    // 确保字符串以 null 结尾
    result[total_size] = '\0';
    
    return result;
}