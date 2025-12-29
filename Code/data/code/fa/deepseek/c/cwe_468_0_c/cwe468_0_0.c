#include <string.h>

/**
 * تنظیم مقادیر آرایه به صفر از ایندکس شروع داده شده برای تعداد مشخصی از عناصر
 * 
 * @param values: آرایه مقادیر
 * @param begin_index: ایندکسی که باید مقادیر از آنجا تنظیم شوند
 * @param count: تعداد مقادیر برای تنظیم
 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    memset(values + begin_index, 0, count * sizeof(long long));
}