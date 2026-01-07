#include <string.h>

/* بالنظر إلى مصفوفة، قم بإعادة تعيين القيم إلى 0 في المصفوفة، بدءًا من الفهرس المحدد وإعادة تعيين العدد المحدد من القيم. استخدم memset لإعادة تعيين القيم.

@param values: مصفوفة القيم
@param begin_index: الفهرس الذي يبدأ منه إعادة تعيين القيم
@param count: عدد القيم التي سيتم إعادة تعيينها */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // تحقق من صحة المدخلات
    }
    
    memset(&values[begin_index], 0, count * sizeof(long long));
}