#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin. Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.

@param directory Gizli dosyanın kaydedileceği dizin.
@param filename Gizli dosyanın dosya adı.
@param content Gizli dosyanın içeriği. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Parametrelerin geçerliliğini kontrol et
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Hata: Geçersiz parametre (NULL)\n");
        return;
    }
    
    // Dizinin var olup olmadığını kontrol et, yoksa oluştur
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0) {
        // Dizin yok, oluşturmaya çalış
        if (mkdir(directory, 0700) != 0) {
            fprintf(stderr, "Hata: Dizin oluşturulamadı '%s': %s\n", 
                    directory, strerror(errno));
            return;
        }
    } else {
        // Dizin var, gerçekten bir dizin mi kontrol et
        if (!S_ISDIR(dir_stat.st_mode)) {
            fprintf(stderr, "Hata: '%s' bir dizin değil\n", directory);
            return;
        }
    }
    
    // Tam dosya yolunu oluştur
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2: '/' ve null terminator
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "Hata: Bellek tahsisi başarısız\n");
        return;
    }
    
    // Tam yolu oluştur
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Dosyayı yalnızca mevcut kullanıcı için okuma/yazma izinleriyle aç
    FILE *file = fopen(full_path, "w");
    if (file == NULL) {
        fprintf(stderr, "Hata: Dosya açılamadı '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // İçeriği dosyaya yaz
    size_t content_len = strlen(content);
    size_t written = fwrite(content, 1, content_len, file);
    
    if (written != content_len) {
        fprintf(stderr, "Hata: İçerik tam olarak yazılamadı '%s'\n", full_path);
        fclose(file);
        free(full_path);
        return;
    }
    
    // Dosyayı kapat
    if (fclose(file) != 0) {
        fprintf(stderr, "Hata: Dosya kapatılamadı '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Dosya izinlerini yalnızca mevcut kullanıcı için okuma/yazma olarak ayarla
    if (chmod(full_path, 0600) != 0) {
        fprintf(stderr, "Uyarı: Dosya izinleri ayarlanamadı '%s': %s\n", 
                full_path, strerror(errno));
        // Dosya başarıyla oluşturuldu, bu yüzden devam et
    }
    
    // Belleği temizle
    free(full_path);
}