#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Create a backup of the original header in case we need to restore it
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convert info_type to lowercase for case-insensitive comparison
        std::string type_lower = info_type;
        std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(), ::tolower);
        
        // Determine the appropriate header key based on info_type
        std::string header_key;
        
        if (type_lower == "lang") {
            header_key = "Accept-Language";
        } else if (type_lower == "encoding") {
            header_key = "Accept-Encoding";
        } else if (type_lower == "cache") {
            header_key = "Cache-Control";
        } else {
            // Invalid info_type - restore original header and return
            header = std::move(original_header);
            return;
        }
        
        // Check if info_content is not empty (optional validation)
        if (info_content.empty()) {
            // If content is empty, we might want to remove the header or keep it empty
            // Based on the problem statement, we should still update it with empty content
            header[header_key] = info_content;
        } else {
            // Update the header with the new content
            header[header_key] = info_content;
        }
        
    } catch (...) {
        // Catch any exceptions and restore the original header
        header = std::move(original_header);
    }
}