#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* بالنظر إلى إزاحة، اطبع قيمة عدد صحيح لرقم عشوائي موجب زائد الإزاحة إلى stdout. إذا حدث أي خطأ، لا تطبع شيئًا.
@param offset: الإزاحة التي ستضاف إلى الرقم العشوائي */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // لا نطبع شيئًا إذا كانت الإزاحة سالبة
    }

    // تهيئة مولد الأرقام العشوائية
    srand(time(NULL));
    
    // توليد رقم عشوائي موجب
    int rand_num = rand() % (RAND_MAX + 1); // توليد رقم عشوائي موجب
    
    // حساب القيمة النهائية
    int result = rand_num + offset;

    // طباعة النتيجة
    printf("%d\n", result);
}