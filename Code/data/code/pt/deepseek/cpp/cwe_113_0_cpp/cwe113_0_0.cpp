#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Make a copy of the original header to restore if something goes wrong
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convert info_type to lowercase for case-insensitive comparison
        std::string type_lower = info_type;
        std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        // Store the information based on the type
        if (type_lower == "lang") {
            header["Accept-Language"] = info_content;
        } else if (type_lower == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (type_lower == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Invalid info_type - restore original header
            header = original_header;
        }
    } catch (...) {
        // If anything goes wrong, restore the original header
        header = original_header;
    }
}