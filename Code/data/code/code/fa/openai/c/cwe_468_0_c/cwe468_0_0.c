#include <string.h>

/**
 * یک آرایه داده شده است، مقادیر را به 0 در آرایه تنظیم کنید، از ایندکس شروع داده شده و تعداد مشخصی از مقادیر را تنظیم کنید.
 *
 * @param values: آرایه مقادیر
 * @param begin_index: ایندکسی که باید مقادیر از آنجا تنظیم شوند
 * @param count: تعداد مقادیر برای تنظیم
 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return;  // برای جلوگیری از دسترسی نامعتبر به آرایه
    }
    memset(&values[begin_index], 0, count * sizeof(long long));
}