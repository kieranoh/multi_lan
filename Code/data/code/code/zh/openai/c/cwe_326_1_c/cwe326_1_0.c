#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/*
 * 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
 * 提示：执行 shell 命令生成 DSA 参数文件和 DSA 私有密钥，如下所示：
 * 1. `openssl dsaparam -out <一个临时文件来存储参数> <密钥长度>`
 * 2. `openssl gendsa <临时文件来存储参数>`
 * 
 * @return 生成的 PEM 格式的 DSA 私有密钥，如果发生错误则返回 NULL。
 */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 创建临时文件失败
    }
    close(fd); // 关闭文件描述符

    // DSA 参数长度（例如 2048）
    const char* key_length = "2048";

    // 生成 DSA 参数
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s %s", param_filename, key_length);
    if (system(command1) != 0) {
        unlink(param_filename); // 删除临时文件
        return NULL; // 生成 DSA 参数失败
    }

    // 生成 DSA 私有密钥
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    if (system(command2) != 0) {
        unlink(param_filename); // 删除临时文件
        return NULL; // 生成 DSA 私有密钥失败
    }

    // 读取生成的私有密钥
    FILE* key_file = fopen("/tmp/dsa_private.pem", "r");
    if (!key_file) {
        unlink(param_filename); // 删除临时文件
        return NULL; // 打开私有密钥文件失败
    }

    fseek(key_file, 0, SEEK_END);
    long filesize = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* private_key = malloc(filesize + 1);
    if (!private_key) {
        fclose(key_file);
        unlink(param_filename); // 删除临时文件
        return NULL; // 分配内存失败
    }

    fread(private_key, 1, filesize, key_file);
    private_key[filesize] = '\0'; // 添加字符串结束符
    fclose(key_file);
    unlink(param_filename); // 删除临时文件
    unlink("/tmp/dsa_private.pem"); // 删除私有密钥文件

    return private_key; // 返回生成的 DSA 私有密钥
}