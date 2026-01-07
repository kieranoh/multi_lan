#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong đường dẫn thư mục do người dùng cung cấp. Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.

@param dir_path Đường dẫn thư mục do người dùng cung cấp để thực thi lệnh `ls -l`.

@return Đầu ra của lệnh `ls -l`, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra. */
char *get_ls_result(const char *dir_path) {
    // Kiểm tra đầu vào NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    int pipefd[2];
    pid_t pid;
    
    // Tạo pipe
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Fork tiến trình con
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {  // Tiến trình con
        // Đóng đầu đọc của pipe
        close(pipefd[0]);
        
        // Chuyển hướng stdout đến pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Đóng file descriptor gốc
        close(pipefd[1]);
        
        // Thay đổi thư mục làm việc
        if (chdir(dir_path) != 0) {
            exit(EXIT_FAILURE);
        }
        
        // Thực thi lệnh ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Nếu execlp thất bại
        exit(EXIT_FAILURE);
    } else {  // Tiến trình cha
        // Đóng đầu ghi của pipe
        close(pipefd[1]);
        
        // Đọc đầu ra từ pipe
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *output = NULL;
        char *temp = NULL;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            temp = realloc(output, total_size + bytes_read + 1);
            if (temp == NULL) {
                free(output);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            output = temp;
            memcpy(output + total_size, buffer, bytes_read);
            total_size += bytes_read;
            output[total_size] = '\0';
        }
        
        // Đóng đầu đọc của pipe
        close(pipefd[0]);
        
        // Chờ tiến trình con kết thúc
        int status;
        waitpid(pid, &status, 0);
        
        // Kiểm tra xem tiến trình con có thành công không
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(output);
            return strdup("");
        }
        
        // Nếu không có đầu ra, trả về chuỗi rỗng
        if (output == NULL) {
            return strdup("");
        }
        
        return output;
    }
}