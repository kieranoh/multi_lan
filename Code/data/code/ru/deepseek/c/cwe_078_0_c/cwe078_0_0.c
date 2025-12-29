#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    int pipefd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_len = 0;
    char buffer[4096];
    ssize_t bytes_read;
    
    // Проверяем, что путь не NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Создаем pipe для чтения вывода команды
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Создаем дочерний процесс
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Дочерний процесс
        close(pipefd[0]); // Закрываем конец для чтения
        
        // Перенаправляем stdout в pipe
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);
        
        // Меняем рабочую директорию
        if (chdir(dir_path) != 0) {
            // Если не удалось сменить директорию, завершаемся с ошибкой
            exit(1);
        }
        
        // Выполняем команду ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Если execlp вернулся, значит произошла ошибка
        exit(1);
    } else {
        // Родительский процесс
        close(pipefd[1]); // Закрываем конец для записи
        
        // Читаем вывод из pipe
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Перераспределяем память для результата
            size_t new_len = result_len + bytes_read;
            if (new_len + 1 > result_size) {
                size_t new_size = result_size == 0 ? 4096 : result_size * 2;
                while (new_len + 1 > new_size) {
                    new_size *= 2;
                }
                
                char *new_result = realloc(result, new_size);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                
                result = new_result;
                result_size = new_size;
            }
            
            // Копируем данные в результат
            memcpy(result + result_len, buffer, bytes_read);
            result_len = new_len;
            result[result_len] = '\0';
        }
        
        close(pipefd[0]);
        
        // Ждем завершения дочернего процесса
        int status;
        waitpid(pid, &status, 0);
        
        // Проверяем, успешно ли завершилась команда
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Если результат пустой, возвращаем пустую строку
            if (result == NULL) {
                result = strdup("");
            }
            return result;
        } else {
            // Если команда завершилась с ошибкой, возвращаем пустую строку
            free(result);
            return strdup("");
        }
    }
}