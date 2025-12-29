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
    
    // إعداد البادئة في buf
    strcpy(buf, "محتوى الملف: ");
    
    // حساب المساحة المتبقية في buf
    int remaining = BUF_SIZE - strlen(buf) - 1; // -1 للحفاظ على مساحة null terminator
    int count = read(fd, buf + strlen(buf), remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // النسخ من buf إلى out
    strcpy(out, buf);
    
    close(fd);
}