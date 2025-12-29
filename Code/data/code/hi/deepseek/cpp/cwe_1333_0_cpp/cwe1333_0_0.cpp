#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 के अनुरूप व्यापक ईमेल सत्यापन पैटर्न
    // यह पैटर्न अधिकांश वैध ईमेल पतों को स्वीकार करता है जबकि सामान्य अमान्य प्रारूपों को अस्वीकार करता है
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // रेगुलर एक्सप्रेशन ऑब्जेक्ट बनाएं
    std::regex email_regex(pattern);
    
    // ईमेल की लंबाई की जांच (RFC 5321 के अनुसार, स्थानीय भाग अधिकतम 64 वर्ण और डोमेन भाग अधिकतम 255 वर्ण)
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // @ प्रतीक की उपस्थिति की जांच
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // स्थानीय भाग (local-part) और डोमेन भाग अलग करें
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // स्थानीय भाग की लंबाई जांच (अधिकतम 64 वर्ण)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // डोमेन भाग की लंबाई जांच (अधिकतम 255 वर्ण)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, pattern);
    }
    
    // डोमेन भाग में कम से कम एक डॉट होना चाहिए
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // डोमेन भाग के हिस्सों की जांच (प्रत्येक भाग 63 वर्ण से अधिक नहीं होना चाहिए)
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string domain_label = domain_part.substr(start, dot_pos - start);
        if (domain_label.empty() || domain_label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        // डोमेन लेबल हाइफन से शुरू या समाप्त नहीं हो सकता
        if (domain_label.front() == '-' || domain_label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        start = dot_pos + 1;
    }
    
    // अंतिम डोमेन लेबल की जांच
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || last_label.length() > 63) {
        return std::make_tuple(false, pattern);
    }
    if (last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, pattern);
    }
    
    // रेगुलर एक्सप्रेशन से मिलान करें
    bool is_valid = std::regex_match(email, email_regex);
    
    // अतिरिक्त जांच: डोमेन भाग में केवल वैध वर्ण हों
    for (char c : domain_part) {
        if (!(std::isalnum(c) || c == '.' || c == '-')) {
            return std::make_tuple(false, pattern);
        }
    }
    
    // अतिरिक्त जांच: क्रमिक डॉट्स नहीं होने चाहिए
    if (email.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // अतिरिक्त जांच: स्थानीय भाग की शुरुआत या अंत में डॉट नहीं होना चाहिए
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    return std::make_tuple(is_valid, pattern);
}