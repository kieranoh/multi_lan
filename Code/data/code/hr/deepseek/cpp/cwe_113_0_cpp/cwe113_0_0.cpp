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
        
        // Determine the header key based on info_type
        std::string header_key;
        
        if (type_lower == "lang") {
            header_key = "Accept-Language";
        } else if (type_lower == "encoding") {
            header_key = "Accept-Encoding";
        } else if (type_lower == "cache") {
            header_key = "Cache-Control";
        } else {
            // Invalid info_type - restore original header and return
            header = original_header;
            return;
        }
        
        // Check if info_content is not empty (basic validation)
        if (info_content.empty()) {
            // Empty content - restore original header and return
            header = original_header;
            return;
        }
        
        // Store the information in the header
        header[header_key] = info_content;
        
    } catch (...) {
        // Catch any exception and restore the original header
        header = original_header;
    }
}