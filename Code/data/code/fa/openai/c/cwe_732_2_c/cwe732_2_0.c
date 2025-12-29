#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // ساختن مسیر کامل فایل
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // ایجاد و نوشتن در فایل
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    
    // نوشتن محتوا در فایل
    fprintf(file, "%s", content);
    fclose(file);
    
    // تنظیم مجوزهای فایل برای فقط کاربر فعلی
    chmod(filepath, S_IRUSR | S_IWUSR);
}