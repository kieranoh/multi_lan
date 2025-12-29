#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // खाली इनपुट के लिए डिफ़ॉल्ट डोमेन URL लौटाएं
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // लक्ष्य URL से प्रोटोकॉल निकालें
    std::string target_lower = target;
    std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // यदि लक्ष्य URL में "https://" शुरू नहीं होता है, तो इसे जोड़ें
    std::string target_with_protocol = target_lower;
    if (target_lower.find("https://") != 0 && target_lower.find("http://") != 0) {
        target_with_protocol = "https://" + target_lower;
    }
    // यदि "http://" से शुरू होता है, तो इसे "https://" में बदलें
    else if (target_lower.find("http://") == 0) {
        target_with_protocol = "https://" + target_lower.substr(7);
    }
    
    // लक्ष्य URL से डोमेन निकालें
    std::string target_domain;
    size_t protocol_end = target_with_protocol.find("://");
    if (protocol_end != std::string::npos) {
        size_t domain_start = protocol_end + 3;
        size_t domain_end = target_with_protocol.find('/', domain_start);
        if (domain_end != std::string::npos) {
            target_domain = target_with_protocol.substr(domain_start, domain_end - domain_start);
        } else {
            target_domain = target_with_protocol.substr(domain_start);
        }
    } else {
        // यदि कोई प्रोटोकॉल नहीं है, तो पहले '/' तक या पूरी स्ट्रिंग लें
        size_t domain_end = target_with_protocol.find('/');
        if (domain_end != std::string::npos) {
            target_domain = target_with_protocol.substr(0, domain_end);
        } else {
            target_domain = target_with_protocol;
        }
    }
    
    // डोमेन की तुलना करें
    std::string domain_lower = domain;
    std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // यह जांचें कि लक्ष्य डोमेन दिए गए डोमेन के भीतर है या नहीं
    // यह सबडोमेन या समान डोमेन की अनुमति देता है
    if (target_domain == domain_lower || 
        (target_domain.length() > domain_lower.length() + 1 && 
         target_domain.substr(target_domain.length() - domain_lower.length() - 1) == "." + domain_lower)) {
        return target_with_protocol;
    } else {
        return "https://" + domain_lower;
    }
}