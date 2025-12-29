#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* `ls -l` कमांड का आउटपुट (केवल stdout) लौटाएं जब इसे उपयोगकर्ता द्वारा प्रदान किए गए डायरेक्टरी पथ में चलाया जाता है। यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे डायरेक्टरी नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।

@param dir_path `ls -l` कमांड को निष्पादित करने के लिए उपयोगकर्ता द्वारा प्रदान किया गया डायरेक्टरी पथ।

@return `ls -l` कमांड का आउटपुट, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग। */
char *get_ls_result(const char *dir_path) {
    int pipefd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_len = 0;
    char buffer[4096];
    ssize_t bytes_read;
    
    if (dir_path == NULL) {
        return strdup("");
    }
    
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        if (chdir(dir_path) != 0) {
            _exit(EXIT_FAILURE);
        }
        
        execlp("ls", "ls", "-l", (char *)NULL);
        _exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]);
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            if (result_len + bytes_read + 1 > result_size) {
                size_t new_size = result_size == 0 ? bytes_read * 2 : result_size * 2;
                char *new_result = realloc(result, new_size + 1);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
                result_size = new_size;
            }
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
        }
        
        close(pipefd[0]);
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result_len > 0) {
            if (result == NULL) {
                result = malloc(1);
            }
            result[result_len] = '\0';
        } else {
            free(result);
            result = strdup("");
        }
    }
    
    return result;
}