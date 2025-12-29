#include <string.h>

/**
 * एक ऐरे दिया गया है, दिए गए प्रारंभ अनुक्रमांक से शुरू करते हुए और दिए गए गिनती संख्या के मानों को 0 पर रीसेट करें। मानों को रीसेट करने के लिए memset का उपयोग करें।
 * 
 * @param values: मानों का ऐरे
 * @param begin_index: मानों को रीसेट करने के लिए प्रारंभ अनुक्रमांक
 * @param count: रीसेट करने के लिए मानों की संख्या
 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    memset(values + begin_index, 0, count * sizeof(long long));
}