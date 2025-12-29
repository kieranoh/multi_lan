#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // التحقق من صحة المدخلات
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "خطأ: مدخلات غير صالحة\n");
        return;
    }
    
    // إنشاء المسار الكامل للملف
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 للفاصل '/' والبايت الختامي '\0'
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "خطأ: فشل في تخصيص الذاكرة\n");
        return;
    }
    
    // بناء المسار الكامل
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // محاولة إنشاء الدليل إذا لم يكن موجودًا
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            // فشل في إنشاء الدليل لسبب آخر غير وجوده مسبقًا
            fprintf(stderr, "خطأ: فشل في إنشاء الدليل '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
        // الدليل موجود بالفعل، وهذا مقبول
    }
    
    // فتح/إنشاء الملف مع أذونات مقيدة (فقط للمالك)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "خطأ: فشل في إنشاء/فتح الملف '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // كتابة المحتوى إلى الملف
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != (ssize_t)content_len) {
        fprintf(stderr, "خطأ: فشل في كتابة المحتوى بالكامل إلى الملف\n");
        close(fd);
        free(full_path);
        return;
    }
    
    // إغلاق الملف وتحرير الذاكرة
    close(fd);
    free(full_path);
    
    // تأكيد النجاح
    printf("تم حفظ الملف السري بنجاح في: %s/%s\n", directory, filename);
}