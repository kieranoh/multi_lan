#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Hasierako URL-a
    std::string url = "https://";
    
    // Aztertu azpidomeinu aurprefiksoa
    std::string trimmed_prefix = subdomain_prefix;
    
    // Kendu hasierako eta amaierako zuriuneak
    auto start = std::find_if_not(trimmed_prefix.begin(), trimmed_prefix.end(), 
                                  [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(trimmed_prefix.rbegin(), trimmed_prefix.rend(),
                                [](unsigned char c) { return std::isspace(c); }).base();
    
    if (start < end) {
        trimmed_prefix = std::string(start, end);
    } else {
        trimmed_prefix.clear();
    }
    
    // Eraiki URL-a
    if (!trimmed_prefix.empty()) {
        // Gehitu azpidomeinua eta puntua
        url += trimmed_prefix + ".";
    }
    
    // Gehitu domeinua
    url += domain;
    
    return url;
}