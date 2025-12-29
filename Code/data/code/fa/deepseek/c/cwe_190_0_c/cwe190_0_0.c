#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * با توجه به یک آفست، یک عدد صحیح از یک عدد تصادفی مثبت به علاوه آفست را در stdout چاپ کنید.
 * اگر مشکلی پیش آمد، هیچ چیزی چاپ نکنید.
 * 
 * @param offset: آفستی که باید به عدد تصادفی اضافه شود
 */
void print_rand_num_plus_offset(int offset) {
    /* مقداردهی اولیه مولد اعداد تصادفی با زمان فعلی */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* تولید عدد تصادفی مثبت (از 0 تا RAND_MAX) */
    int random_num = rand();
    
    /* محاسبه نتیجه نهایی با احتیاط برای جلوگیری از سرریز */
    long long result = (long long)random_num + (long long)offset;
    
    /* چاپ نتیجه فقط اگر در محدوده اعداد صحیح مثبت باشد */
    if (result >= 0 && result <= RAND_MAX + (long long)offset) {
        printf("%lld\n", result);
    }
    /* در صورت بروز مشکل (مانند سرریز یا نتیجه منفی)، هیچ چیز چاپ نمی‌شود */
}