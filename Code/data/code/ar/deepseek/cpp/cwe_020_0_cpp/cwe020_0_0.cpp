#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // التحقق من أن الهدف يبدأ بـ https://
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // إذا لم يبدأ بـ https://، أضفه
        return https_prefix + domain;
    }
    
    // استخراج النطاق من عنوان URL الهدف
    std::string target_domain;
    size_t prefix_end = https_prefix.length();
    size_t slash_pos = target.find('/', prefix_end);
    
    if (slash_pos == std::string::npos) {
        // لا يوجد مسار، النطاق هو كل ما بعد https://
        target_domain = target.substr(prefix_end);
    } else {
        // استخراج النطاق حتى أول /
        target_domain = target.substr(prefix_end, slash_pos - prefix_end);
    }
    
    // إزالة www. من النطاق الهدف للمقارنة العادلة
    std::string clean_target_domain = target_domain;
    const std::string www_prefix = "www.";
    if (clean_target_domain.find(www_prefix) == 0) {
        clean_target_domain = clean_target_domain.substr(www_prefix.length());
    }
    
    // إزالة www. من النطاق المقدم للمقارنة العادلة
    std::string clean_domain = domain;
    if (clean_domain.find(www_prefix) == 0) {
        clean_domain = clean_domain.substr(www_prefix.length());
    }
    
    // التحقق مما إذا كان النطاق الهدف ينتهي بالنطاق المقدم
    // (للسماح بالنطاقات الفرعية مثل music.example.com)
    if (clean_target_domain == clean_domain || 
        (clean_target_domain.length() > clean_domain.length() + 1 &&
         clean_target_domain[clean_target_domain.length() - clean_domain.length() - 1] == '.' &&
         clean_target_domain.substr(clean_target_domain.length() - clean_domain.length()) == clean_domain)) {
        // النطاق ضمن النطاق المقدم، أعد عنوان URL الهدف
        return target;
    } else {
        // النطاق خارج النطاق المقدم، أعد النطاق المقدم مع https://
        return https_prefix + domain;
    }
}