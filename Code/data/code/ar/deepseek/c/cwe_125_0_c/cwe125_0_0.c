#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // التحقق من المؤشرات الفارغة
    if (prices == NULL || index_str == NULL) {
        return -1;
    }
    
    // التحقق من أن السلسلة ليست فارغة
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // التحقق من أن جميع الأحرف في السلسلة هي أرقام
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // تحويل السلسلة إلى عدد صحيح
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // التحقق من نجاح التحويل
    if (*endptr != '\0') {
        return -1;
    }
    
    // التحقق من أن الفهرس ضمن النطاق
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // إرجاع السعر في الفهرس المحدد
    return prices[index];
}