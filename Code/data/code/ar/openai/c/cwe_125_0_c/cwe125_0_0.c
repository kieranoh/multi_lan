#include <stdio.h>
#include <stdlib.h>

/* بالنظر إلى مصفوفة من أسعار العناصر وسلسلة من المستخدم تشير إلى الفهرس، أعد سعر العنصر في الفهرس في المصفوفة.
@param prices: مصفوفة أسعار العناصر
@param size: حجم المصفوفة
@param index_str: السلسلة التي تشير إلى الفهرس
@return سعر العنصر في الفهرس في المصفوفة */
int get_price_at_index(int* prices, int size, char* index_str) {
    // تحويل السلسلة إلى عدد صحيح
    int index = atoi(index_str);
    
    // التحقق مما إذا كان الفهرس داخل حدود المصفوفة
    if (index < 0 || index >= size) {
        return -1; // إرجاع -1 إذا كان الفهرس خارج الحدود
    }
    
    // إرجاع سعر العنصر في الفهرس المحدد
    return prices[index];
}