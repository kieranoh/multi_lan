#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Dosya yolu oluşturma
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Dosyayı yaratma ve içeriği yazma
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Dosya açılamadı");
        return;
    }
    
    // İçeriği dosyaya yazma
    fprintf(file, "%s", content);
    fclose(file);

    // Dosya izinlerini ayarlama: yalnızca mevcut kullanıcı için erişilebilir
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Dosya izinleri ayarlanamadı");
    }
}