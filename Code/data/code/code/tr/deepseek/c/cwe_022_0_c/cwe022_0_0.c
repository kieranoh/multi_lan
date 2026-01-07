#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
#endif

/* Kullanıcı tarafından sağlanan bir dizin yolu ve bir dosya adı verildiğinde, dosyayı dizinden okuyun ve içeriğini döndürün. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döndürün. Döndürülen dize, çağıran tarafından serbest bırakılacaktır.

@param filename Okunacak dosyanın adı, bir kullanıcı tarafından talep edilmiştir.
@param dir_path Dosyanın bulunduğu dizinin yolu.

@return Dosya mevcutsa ve erişilebilir durumdaysa içeriği, aksi takdirde boş bir dize. */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Parametrelerin geçerliliğini kontrol et
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // Tam dosya yolunu oluştur
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Dizin yolunun sonunda ayraç olup olmadığını kontrol et
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Tam yol için bellek ayır
    size_t full_path_len = dir_len + needs_separator + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Tam yolu oluştur
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, (char[]){PATH_SEPARATOR, '\0'});
    }
    strcat(full_path, filename);
    
    // Dosya varlığını ve erişim izinlerini kontrol et
    FILE *file = fopen(full_path, "rb");  // Binary modda aç
    free(full_path);  // Tam yolu artık ihtiyacımız yok
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Dosya boyutunu belirle
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // Dosyayı başa sar
    rewind(file);
    
    // Dosya içeriği için bellek ayır (null terminator için +1)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Dosyayı oku
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // String'i null-terminated yap
    content[file_size] = '\0';
    
    return content;
}