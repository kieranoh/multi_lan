#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // 检查输入参数是否有效
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // 创建管道用于读取子进程的输出
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // 创建子进程执行命令
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // 子进程
        
        // 关闭管道的读端
        close(pipefd[0]);
        
        // 将标准输出重定向到管道的写端
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // 关闭原始的文件描述符
        close(pipefd[1]);
        
        // 执行 ls -l 命令
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // 如果 execlp 失败，退出子进程
        _exit(EXIT_FAILURE);
    } else {
        // 父进程
        
        // 关闭管道的写端
        close(pipefd[1]);
        
        // 读取子进程的输出
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            // 确保缓冲区以空字符结尾
            buffer[bytes_read] = '\0';
            
            // 重新分配内存以容纳新数据
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = new_result;
            
            // 复制新数据到结果字符串
            memcpy(result + total_size, buffer, bytes_read + 1);
            total_size += bytes_read;
        }
        
        // 关闭管道的读端
        close(pipefd[0]);
        
        // 等待子进程结束
        int status;
        waitpid(pid, &status, 0);
        
        // 检查子进程是否成功执行
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // 如果之前没有分配内存（没有输出），返回空字符串
            if (result == NULL) {
                return strdup("");
            }
            
            // 确保结果字符串以空字符结尾
            result[total_size] = '\0';
            return result;
        } else {
            // 命令执行失败，释放内存并返回空字符串
            free(result);
            return strdup("");
        }
    }
}