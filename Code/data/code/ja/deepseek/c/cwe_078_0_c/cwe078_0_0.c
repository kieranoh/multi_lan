#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* `ls -l` コマンドがユーザー提供のディレクトリパスで実行されたときの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。

@param dir_path `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。

@return `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。 */
char *get_ls_result(const char *dir_path) {
    if (dir_path == NULL) {
        return strdup("");
    }
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // 子プロセス
        close(pipefd[0]);
        
        // 標準出力をパイプにリダイレクト
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        
        // 標準エラーを/dev/nullにリダイレクトしてエラーメッセージを抑制
        FILE *null_file = fopen("/dev/null", "w");
        if (null_file != NULL) {
            dup2(fileno(null_file), STDERR_FILENO);
            fclose(null_file);
        }
        
        // ls -l コマンドを実行
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // execlpが失敗した場合
        _exit(EXIT_FAILURE);
    } else {
        // 親プロセス
        close(pipefd[1]);
        
        // 子プロセスの終了を待つ
        int status;
        waitpid(pid, &status, 0);
        
        // 子プロセスが正常終了しなかった場合
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            close(pipefd[0]);
            return strdup("");
        }
        
        // パイプから出力を読み取る
        char buffer[4096];
        size_t total_size = 0;
        size_t capacity = 4096;
        char *result = malloc(capacity);
        if (result == NULL) {
            close(pipefd[0]);
            return strdup("");
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 必要に応じてメモリを再確保
            if (total_size + bytes_read + 1 > capacity) {
                capacity = (total_size + bytes_read + 1) * 2;
                char *new_result = realloc(result, capacity);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    return strdup("");
                }
                result = new_result;
            }
            
            strcat(result, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // 読み取りエラーのチェック
        if (bytes_read == -1) {
            free(result);
            return strdup("");
        }
        
        // 結果が空の場合は空文字列を返す
        if (total_size == 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}