#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* `ls -l` komutunun, kullanıcı tarafından sağlanan dizin yolunda çalıştırıldığında döndürdüğü çıktıyı (sadece stdout) döndürün. Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndürün.

@param dir_path `ls -l` komutunu çalıştırmak için kullanıcı tarafından sağlanan dizin yolu.

@return `ls -l` komutunun çıktısı veya herhangi bir hata oluşursa boş bir dize. */
char *get_ls_result(const char *dir_path) {
    // Geçersiz giriş kontrolü
    if (dir_path == NULL) {
        return strdup("");
    }
    
    int pipefd[2];
    pid_t pid;
    
    // Boru oluştur
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Çatal oluştur
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Çocuk süreç
        close(pipefd[0]); // Okuma ucunu kapat
        
        // stdout'u borunun yazma ucuna yönlendir
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // stderr'i yok et (hata mesajlarını görmezden gel)
        int dev_null = open("/dev/null", O_WRONLY);
        if (dev_null != -1) {
            dup2(dev_null, STDERR_FILENO);
            close(dev_null);
        }
        
        // ls -l komutunu çalıştır
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // execlp başarısız olursa
        _exit(EXIT_FAILURE);
    } else {
        // Ebeveyn süreç
        close(pipefd[1]); // Yazma ucunu kapat
        
        // Çıktıyı okumak için tampon
        size_t buffer_size = 4096;
        size_t total_size = 0;
        char *result = malloc(buffer_size);
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        char temp_buffer[1024];
        
        while ((bytes_read = read(pipefd[0], temp_buffer, sizeof(temp_buffer) - 1)) > 0) {
            temp_buffer[bytes_read] = '\0';
            
            // Gerekirse tamponu genişlet
            if (total_size + bytes_read + 1 > buffer_size) {
                buffer_size *= 2;
                char *new_result = realloc(result, buffer_size);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
            }
            
            // Okunan veriyi ekle
            strcat(result + total_size, temp_buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Çocuk sürecin durumunu kontrol et
        int status;
        waitpid(pid, &status, 0);
        
        // Komut başarısız olduysa boş dize döndür
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // Hiç veri okunmadıysa veya okuma hatası olduysa
        if (bytes_read == -1 || total_size == 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}