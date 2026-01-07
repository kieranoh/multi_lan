#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // تحقق مما إذا كانت user_id فارغة أو غير صالحة
    if (user_id.empty()) {
        return "";
    }
    
    // بناء URL للاستعلام
    return api_url + "/" + user_id;
}