#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Verificar se o caminho é NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Criar pipe para comunicação entre processos
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Fork para criar processo filho
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Processo filho
        close(pipefd[0]);  // Fechar extremidade de leitura do pipe
        
        // Redirecionar stdout para o pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Executar ls -l no diretório especificado
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // Se execlp falhar, sair com código de erro
        _exit(EXIT_FAILURE);
    } else {
        // Processo pai
        close(pipefd[1]);  // Fechar extremidade de escrita do pipe
        
        // Ler a saída do comando
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
        
        close(pipefd[0]);
        
        // Esperar pelo processo filho terminar
        int status;
        waitpid(pid, &status, 0);
        
        // Verificar se o comando foi executado com sucesso
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(output);
            return strdup("");
        }
        
        // Se nenhuma saída foi lida, retornar string vazia
        if (output == NULL) {
            return strdup("");
        }
        
        return output;
    }
}