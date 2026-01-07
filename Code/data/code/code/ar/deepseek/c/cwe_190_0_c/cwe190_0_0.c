#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* تهيئة مولد الأرقام العشوائية */
    srand((unsigned int)time(NULL));
    
    /* توليد رقم عشوائي موجب */
    int random_num = rand();
    
    /* التأكد من أن الرقم موجب (rand() يعيد قيمة بين 0 و RAND_MAX) */
    if (random_num < 0) {
        /* إذا كان الرقم سالباً، لا تطبع شيئاً */
        return;
    }
    
    /* حساب النتيجة مع التحقق من تجاوز السعة */
    long long result = (long long)random_num + (long long)offset;
    
    /* التحقق من أن النتيجة موجبة */
    if (result <= 0) {
        /* إذا لم تكن النتيجة موجبة، لا تطبع شيئاً */
        return;
    }
    
    /* طباعة النتيجة */
    printf("%lld\n", result);
}