#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // إنشاء أنبوب للاتصال بين العملية الرئيسية والفرعية
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // إنشاء عملية فرعية
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // العملية الفرعية
        close(pipefd[0]);  // إغلاق نهاية القراءة
        
        // إعادة توجيه stdout إلى نهاية الكتابة في الأنبوب
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // إعادة توجيه stderr إلى /dev/null لتجاهل رسائل الخطأ
        FILE *null_file = fopen("/dev/null", "w");
        if (null_file) {
            dup2(fileno(null_file), STDERR_FILENO);
            fclose(null_file);
        }
        
        close(pipefd[1]);  // إغلاق الواصلة الأصلية
        
        // تغيير الدليل إلى المسار المحدد
        if (chdir(dir_path) != 0) {
            _exit(EXIT_FAILURE);
        }
        
        // تنفيذ أمر ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // إذا وصلنا إلى هنا، فشل execlp
        _exit(EXIT_FAILURE);
    } else {
        // العملية الرئيسية
        close(pipefd[1]);  // إغلاق نهاية الكتابة
        
        // قراءة الإخراج من الأنبوب
        char buffer[4096];
        size_t total_size = 0;
        size_t buffer_capacity = 4096;
        char *result = malloc(buffer_capacity);
        
        if (!result) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // التأكد من وجود مساحة كافية
            if (total_size + bytes_read + 1 > buffer_capacity) {
                buffer_capacity = (total_size + bytes_read + 1) * 2;
                char *new_result = realloc(result, buffer_capacity);
                if (!new_result) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
            }
            
            // إضافة البيانات إلى النتيجة
            strcat(result, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // انتظار انتهاء العملية الفرعية والتحقق من حالتها
        int status;
        waitpid(pid, &status, 0);
        
        // إذا فشلت العملية الفرعية، أعد سلسلة فارغة
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // إذا لم يكن هناك إخراج، أعد سلسلة فارغة
        if (strlen(result) == 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}