#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Giriş parametresini kontrol et
    if (results == NULL) {
        return NULL;
    }
    
    // Geçici dosya adı için şablon
    char template[] = "/tmp/results_XXXXXX";
    
    // Geçici dosya oluştur
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Sonuçları dosyaya yaz
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template); // Dosyayı sil
        return NULL;
    }
    
    // Dosyayı kapat
    close(fd);
    
    // Dosya adını kopyala ve döndür
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Bellek hatası durumunda dosyayı temizle
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}