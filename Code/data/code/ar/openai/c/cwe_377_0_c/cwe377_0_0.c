#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// قم بإنشاء ملف مؤقت، واكتب النتائج المقدمة فيه، وأعد اسم الملف للقراءة لاحقًا.
char* write_results(const char* results) {
    // إنشاء اسم ملف مؤقت
    char* filename = malloc(32);
    if (filename == NULL) {
        return NULL; // تحقق من تخصيص الذاكرة
    }
    
    // إنشاء اسم الملف باستخدام الوقت الحالي
    time_t now = time(NULL);
    snprintf(filename, 32, "results_%ld.txt", now);
    
    // فتح الملف للكتابة
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename); // تحرير الذاكرة إذا فشل فتح الملف
        return NULL;
    }
    
    // كتابة النتائج إلى الملف
    fprintf(file, "%s", results);
    
    // إغلاق الملف
    fclose(file);
    
    // إعادة اسم الملف
    return filename;
}