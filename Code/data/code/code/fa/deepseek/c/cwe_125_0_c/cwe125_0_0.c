#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/**
 * با توجه به یک آرایه از قیمت‌های کالا و یک رشته از کاربر که نشان‌دهنده ایندکس است، قیمت کالای موجود در ایندکس آرایه را برگردانید.
 * 
 * @param prices: آرایه‌ای از قیمت‌های کالا
 * @param size: اندازه آرایه
 * @param index_str: رشته‌ای که ایندکس را نشان می‌دهد
 * @return قیمت کالای موجود در ایندکس آرایه یا -1 در صورت خطا
 */
int get_price_at_index(int* prices, int size, char* index_str) {
    // بررسی پارامترهای ورودی
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // بررسی اینکه رشته خالی نباشد
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // بررسی اینکه رشته فقط شامل ارقام باشد (و یک علامت منفی در ابتدا در صورت وجود)
    char* ptr = index_str;
    
    // اجازه دادن به علامت منفی در ابتدا
    if (*ptr == '-') {
        ptr++;
    }
    
    // بررسی باقی کاراکترها که باید رقم باشند
    while (*ptr != '\0') {
        if (!isdigit((unsigned char)*ptr)) {
            return -1;
        }
        ptr++;
    }
    
    // تبدیل رشته به عدد
    long index_long = strtol(index_str, NULL, 10);
    
    // بررسی محدوده عدد
    if (index_long < INT_MIN || index_long > INT_MAX) {
        return -1;
    }
    
    int index = (int)index_long;
    
    // بررسی اینکه ایندکس در محدوده معتبر آرایه باشد
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // برگرداندن قیمت در ایندکس مورد نظر
    return prices[index];
}