#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Erabiltzaile ID-a hutsik edo baliogabea bada, itzuli string huts bat
    if (user_id.empty()) {
        return "";
    }
    
    // Egiaztatu erabiltzaile ID-a baliogabea den (espazio zuriz soilik osatuta badago)
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // URL-a eraiki
    std::string result = api_url;
    
    // Ziurtatu API URL-ak '/' amaiera duela
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // Gehitu erabiltzaile ID-a
    result += user_id;
    
    return result;
}