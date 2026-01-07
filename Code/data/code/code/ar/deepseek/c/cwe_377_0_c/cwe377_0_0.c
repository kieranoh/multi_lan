#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <errno.h>
#endif

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }

    // إنشاء اسم ملف مؤقت
    char* temp_filename = NULL;
    
#ifdef _WIN32
    // تنفيذ لنظام Windows
    char temp_path[MAX_PATH];
    char temp_file[MAX_PATH];
    
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    if (GetTempFileNameA(temp_path, "res", 0, temp_file) == 0) {
        return NULL;
    }
    
    temp_filename = strdup(temp_file);
#else
    // تنفيذ لأنظمة Unix/Linux
    const char* temp_dir = getenv("TMPDIR");
    if (temp_dir == NULL) {
        temp_dir = "/tmp";
    }
    
    // إنشاء قالب لاسم الملف
    char template[512];
    snprintf(template, sizeof(template), "%s/results_XXXXXX", temp_dir);
    
    // إنشاء ملف مؤقت باستخدام mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    temp_filename = strdup(template);
    close(fd); // سنقوم بفتح الملف مرة أخرى للكتابة
#endif

    if (temp_filename == NULL) {
        return NULL;
    }

    // فتح الملف للكتابة
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        free(temp_filename);
        return NULL;
    }

    // كتابة المحتوى إلى الملف
    size_t len = strlen(results);
    size_t written = fwrite(results, 1, len, file);
    
    if (written != len) {
        fclose(file);
        free(temp_filename);
        return NULL;
    }

    // إغلاق الملف
    if (fclose(file) != 0) {
        free(temp_filename);
        return NULL;
    }

    return temp_filename;
}