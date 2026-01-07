#include <stdio.h>
#include <stdlib.h>

/* با توجه به یک آرایه از قیمت‌های کالا و یک رشته از کاربر که نشان‌دهنده ایندکس است، قیمت کالای موجود در ایندکس آرایه را برگردانید.

@param prices: آرایه‌ای از قیمت‌های کالا
@param size: اندازه آرایه
@param index_str: رشته‌ای که ایندکس را نشان می‌دهد
@return قیمت کالای موجود در ایندکس آرایه */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str);  // تبدیل رشته به عدد صحیح

    // بررسی اینکه آیا ایندکس در محدوده آرایه است یا خیر
    if (index < 0 || index >= size) {
        return -1;  // بازگشت -1 در صورت ایندکس نامعتبر
    }

    return prices[index];  // بازگشت قیمت کالای موجود در ایندکس
}