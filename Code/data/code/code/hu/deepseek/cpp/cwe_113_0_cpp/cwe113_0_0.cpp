#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Segédfüggvény a string kisbetűssé alakításához
std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lower_str;
}

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Érvényes információs típusok és a hozzájuk tartozó fejléc kulcsok
    static const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };
    
    // Az info_type kisbetűssé alakítása a kis- és nagybetűk megkülönböztetése nélküli kezelés érdekében
    std::string lower_info_type = to_lower(info_type);
    
    // Ellenőrzés, hogy az info_type érvényes-e
    auto it = valid_types.find(lower_info_type);
    if (it != valid_types.end()) {
        // Ha érvényes, frissítsük a fejlécet
        header[it->second] = info_content;
    }
    // Ha nem érvényes, nem csinálunk semmit - a header változatlan marad
}