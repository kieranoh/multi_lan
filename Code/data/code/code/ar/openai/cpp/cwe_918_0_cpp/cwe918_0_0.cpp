#include <string>
#include <iostream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // التحقق مما إذا كانت البادئة الفرعية فارغة أو غير صالحة
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // إرجاع النطاق فقط
    } else {
        return "https://" + subdomain_prefix + "." + domain; // إرجاع الرابط مع البادئة الفرعية
    }
}