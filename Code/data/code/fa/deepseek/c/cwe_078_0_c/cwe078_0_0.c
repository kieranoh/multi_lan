#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // آرایه‌ای برای ذخیره خروجی
    char *output = NULL;
    size_t output_size = 0;
    
    // ایجاد یک پایپ برای خواندن خروجی فرآیند فرزند
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // ایجاد فرآیند فرزند
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // کد فرآیند فرزند
        close(pipefd[0]); // انتهای خواندن پایپ را ببند
        
        // تغییر مسیر stdout به انتهای نوشتن پایپ
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO); // خطاها را هم به پایپ هدایت می‌کنیم
        close(pipefd[1]);
        
        // تغییر دایرکتوری کاری
        if (chdir(dir_path) != 0) {
            exit(EXIT_FAILURE);
        }
        
        // اجرای دستور ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // اگر execlp موفق نبود
        exit(EXIT_FAILURE);
    } else {
        // کد فرآیند والد
        close(pipefd[1]); // انتهای نوشتن پایپ را ببند
        
        // خواندن خروجی از پایپ
        char buffer[4096];
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // تخصیص مجدد حافظه برای ذخیره خروجی
            char *new_output = realloc(output, output_size + bytes_read + 1);
            if (new_output == NULL) {
                free(output);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            output = new_output;
            memcpy(output + output_size, buffer, bytes_read);
            output_size += bytes_read;
            output[output_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // منتظر پایان فرآیند فرزند بمان
        int status;
        waitpid(pid, &status, 0);
        
        // اگر فرآیند فرزند با خطا خاتمه یافت یا خروجی خالی است
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0 || output == NULL) {
            free(output);
            return strdup("");
        }
        
        // اگر خروجی داریم، آن را برگردان
        if (output == NULL) {
            return strdup("");
        }
        
        return output;
    }
}