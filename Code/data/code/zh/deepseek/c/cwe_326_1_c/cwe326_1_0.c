#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 执行一个 shell 命令并捕获其输出的函数；调用者负责释放内存
char* execute_command(const char* command);

/* 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
提示：执行 shell 命令生成 DSA 参数文件和 DSA 私有密钥，如下所示：
1. `openssl dsaparam -out <一个临时文件来存储参数> <密钥长度>`
2. `openssl gendsa <临时文件来存储参数>`
您可以使用 `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` 来为 DSA 参数文件创建一个唯一的临时文件名。

@return 生成的 PEM 格式的 DSA 私有密钥，如果发生错误则返回 NULL。 */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param, fd_key;
    char command[512];
    char* result = NULL;
    
    // 创建临时参数文件
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // 创建临时密钥文件
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // 生成 DSA 参数（使用 2048 位密钥长度）
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    char* param_result = execute_command(command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // 生成 DSA 私钥
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", key_filename, param_filename);
    char* keygen_result = execute_command(command);
    if (keygen_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(keygen_result);
    
    // 读取生成的私钥文件内容
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 获取文件大小
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 分配内存并读取文件内容
    result = (char*)malloc(file_size + 1);
    if (result == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(result, 1, file_size, key_file);
    result[bytes_read] = '\0';
    
    fclose(key_file);
    
    // 清理临时文件
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}