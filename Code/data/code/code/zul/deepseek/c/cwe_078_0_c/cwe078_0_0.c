#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_ls_result(const char *dir_path) {
    // パイプのファイル記述子
    int pipefd[2];
    pid_t pid;
    
    // パイプの作成
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // 子プロセスの作成
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // 子プロセス: ls -l を実行
        close(pipefd[0]);  // 読み取り端を閉じる
        
        // 標準出力をパイプの書き込み端にリダイレクト
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // ls -l コマンドを実行
        if (dir_path == NULL || strlen(dir_path) == 0) {
            execlp("ls", "ls", "-l", NULL);
        } else {
            execlp("ls", "ls", "-l", dir_path, NULL);
        }
        
        // execlpが失敗した場合のみここに到達
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス: 子プロセスの出力を読み取る
        close(pipefd[1]);  // 書き込み端を閉じる
        
        // 出力を読み取るためのバッファ
        char *result = NULL;
        size_t total_size = 0;
        char buffer[4096];
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // メモリの再割り当て
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // 子プロセスの終了を待つ
        int status;
        waitpid(pid, &status, 0);
        
        // コマンドが失敗した場合（終了ステータスが0以外）
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // 何も読み取れなかった場合
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}