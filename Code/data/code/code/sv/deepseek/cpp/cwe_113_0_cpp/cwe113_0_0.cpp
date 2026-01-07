#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Create a copy of the original header in case we need to revert
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Check the info_type and map to appropriate header key
        if (info_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (info_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (info_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Invalid info_type - revert to original header
            header = original_header;
            return;
        }
        
        // If we reach here, the update was successful
        return;
        
    } catch (...) {
        // If any exception occurs, revert to original header
        header = original_header;
    }
}