#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <sstream>

// 执行一个 shell 命令并捕获其输出的函数；调用者负责释放内存；不需要实现这个函数，因为它会在后面提供（但在这里声明，以便可以使用它）。
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 创建临时参数文件
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd); // 关闭文件描述符，我们只需要文件名

    // 创建临时密钥文件
    char key_filename[] = "/tmp/keyXXXXXX";
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(key_fd);

    try {
        // 步骤1: 生成 DSA 参数
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
        std::string param_result = execute_command(param_command);
        
        // 检查命令是否成功执行（这里假设 execute_command 在失败时返回非空字符串或抛出异常）
        // 在实际实现中，可能需要根据 execute_command 的具体行为进行调整

        // 步骤2: 生成 DSA 私钥
        std::string key_command = "openssl gendsa " + std::string(param_filename) + " -out " + std::string(key_filename);
        std::string key_result = execute_command(key_command);

        // 读取生成的密钥文件
        std::ifstream key_file(key_filename, std::ios::binary);
        if (!key_file.is_open()) {
            throw std::runtime_error("无法打开生成的密钥文件");
        }

        std::stringstream buffer;
        buffer << key_file.rdbuf();
        std::string key_content = buffer.str();

        // 清理临时文件
        unlink(param_filename);
        unlink(key_filename);

        // 检查密钥内容是否为空
        if (key_content.empty()) {
            return "";
        }

        return key_content;

    } catch (const std::exception& e) {
        // 清理临时文件
        unlink(param_filename);
        unlink(key_filename);
        return "";
    } catch (...) {
        // 清理临时文件
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }
}