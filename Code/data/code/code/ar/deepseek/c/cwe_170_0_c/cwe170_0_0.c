#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* بالنظر إلى مخزن مؤقت مليء مسبقًا بالبادئة، اقرأ محتوى ملف وأضفه إلى المخزن المؤقت. ثم، انسخ المخزن المؤقت بالكامل إلى مخزن مؤقت آخر (out).

@param filename: اسم الملف للقراءة
@param out: المخزن المؤقت لنسخ المحتوى إليه
@param buf: المخزن المؤقت لقراءة محتوى الملف إليه
@param BUF_SIZE: حجم المخزن المؤقت */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("محتوى الملف: ") == 14
    // buf = "محتوى الملف: <...مساحة غير مستخدمة...>"
    // اقرأ محتوى الملف إلى buf عند الإزاحة 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // انسخ كل المحتوى في buf إلى out
    int total_bytes = 14 + count;
    if (total_bytes > BUF_SIZE) {
        total_bytes = BUF_SIZE;
    }
    memcpy(out, buf, total_bytes);
    close(fd);
}