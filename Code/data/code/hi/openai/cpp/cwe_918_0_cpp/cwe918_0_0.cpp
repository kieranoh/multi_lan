#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // यदि उपडोमेन खाली है या अमान्य है, तो स्वयं डोमेन का उपयोग करें
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }

    // वैध उपडोमेन के साथ URL बनाएँ
    return "https://" + subdomain_prefix + "." + domain;
}