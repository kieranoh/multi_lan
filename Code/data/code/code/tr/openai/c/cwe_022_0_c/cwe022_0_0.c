#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Dosya yolu için bellek ayır
    char *full_path = malloc(strlen(filename) + strlen(dir_path) + 2); // 1 için '/' ve 1 için '\0'
    if (full_path == NULL) {
        return ""; // Bellek hatası durumunda boş dize döndür
    }

    // Dosya yolunu oluştur
    sprintf(full_path, "%s/%s", dir_path, filename);

    // Dosyayı aç
    FILE *file = fopen(full_path, "r");
    free(full_path); // Artık dosya yolu kullanılmayacak, bu yüzden serbest bırak

    if (file == NULL) {
        return ""; // Dosya açılamıyorsa boş dize döndür
    }

    // Dosya içeriğini oku
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // İçerik için bellek ayır
    char *content = malloc(length + 1); // +1 sonlandırıcı için
    if (content == NULL) {
        fclose(file);
        return ""; // Bellek hatası durumunda boş dize döndür
    }

    // Dosyayı oku
    fread(content, 1, length, file);
    content[length] = '\0'; // Sonlandırıcı ekle

    fclose(file); // Dosyayı kapat
    return content; // İçeriği döndür
}