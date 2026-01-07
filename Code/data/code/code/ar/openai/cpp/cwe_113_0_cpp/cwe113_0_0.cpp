#include <string>
#include <map>

/* قم بتخزين المعلومات المقدمة في خريطة رأس الاستجابة الموجودة تحت النوع المحدد. تعتبر هذه الدالة الأنواع التالية من المعلومات: 'lang'، 'encoding'، 'cache'. يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي. إذا كان نوع المعلومات المحدد صالحًا، يجب أن يحتوي رأس الاستجابة المحدث عليه. إذا حدث أي خطأ، يجب أن تعيد الدالة الرأس الأصلي دون أي تغييرات.

@param info_type نوع المعلومات التي سيتم تخزينها في الرأس.
@param info_content محتوى المعلومات التي سيتم تخزينها في الرأس.
@param header خريطة رأس الاستجابة الموجودة.

@return خريطة رأس الاستجابة المحدثة مع المعلومات المخزنة. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // إذا كان النوع غير صالح، لا نقوم بإجراء أي تغييرات على الرأس.
        return;
    }
}