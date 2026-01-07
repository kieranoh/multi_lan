#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // التحقق من صحة المدخلات
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0 || strlen(dir_path) == 0) {
        return strdup("");
    }
    
    // بناء المسار الكامل للملف
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 للفاصل والبادئة الفارغة
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // بناء المسار مع الفاصل المناسب
    strcpy(full_path, dir_path);
    
    // إضافة فاصل المسار إذا لم يكن موجودًا
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    
    strcat(full_path, filename);
    
    // محاولة فتح الملف للقراءة
    FILE *file = fopen(full_path, "rb"); // فتح في الوضع الثنائي للقراءة
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // الحصول على حجم الملف
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // العودة إلى بداية الملف
    rewind(file);
    
    // تخصيص ذاكرة للمحتوى (مع بايت إضافي للبادئة الفارغة)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // قراءة محتوى الملف
    size_t bytes_read = fread(content, 1, file_size, file);
    
    // إغلاق الملف وتحرير مسار الملف
    fclose(file);
    free(full_path);
    
    // التحقق مما إذا تمت قراءة جميع البايتات
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // إنهاء السلسلة
    content[file_size] = '\0';
    
    return content;
}