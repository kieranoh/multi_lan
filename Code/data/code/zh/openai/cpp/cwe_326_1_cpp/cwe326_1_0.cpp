#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

/* 生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。
提示：执行 shell 命令生成 DSA 参数文件和 DSA 私有密钥，如下所示：
1. `openssl dsaparam -out <一个临时文件来存储参数> <密钥长度>`
2. `openssl gendsa <存储参数的临时文件>`
您可以使用 `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` 创建一个唯一的临时文件名用于 DSA 参数文件。

@return 生成的 PEM 格式的 DSA 私有密钥，如果发生错误则返回 NULL。 */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 密钥长度，通常使用 2048 位
    char param_filename[] = "/tmp/tempXXXXXX"; // 临时文件名模板
    int fd = mkstemp(param_filename); // 创建临时文件
    if (fd == -1) {
        return ""; // 返回空字符串表示错误
    }
    
    // 生成 DSA 参数
    std::string command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command) != "") {
        close(fd);
        return ""; // 返回空字符串表示错误
    }

    // 生成 DSA 私钥
    command = "openssl gendsa -out /dev/stdout " + std::string(param_filename);
    std::string private_key = execute_command(command);

    // 关闭并删除临时文件
    close(fd);
    unlink(param_filename);

    return private_key; // 返回生成的 DSA 私有密钥
}