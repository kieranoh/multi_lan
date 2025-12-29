#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Helper function to extract content between XML tags
    auto extract_tag_content = [](const std::string& data, const std::string& tag) -> std::string {
        std::string open_tag = "<" + tag + ">";
        std::string close_tag = "</" + tag + ">";
        
        size_t start_pos = data.find(open_tag);
        if (start_pos == std::string::npos) return "";
        
        start_pos += open_tag.length();
        size_t end_pos = data.find(close_tag, start_pos);
        if (end_pos == std::string::npos) return "";
        
        return data.substr(start_pos, end_pos - start_pos);
    };
    
    // Find all student blocks
    std::vector<std::string> student_blocks;
    std::string search_str = "<student>";
    std::string end_str = "</student>";
    
    size_t pos = 0;
    while (pos < xml_data.length()) {
        size_t start_pos = xml_data.find(search_str, pos);
        if (start_pos == std::string::npos) break;
        
        start_pos += search_str.length();
        size_t end_pos = xml_data.find(end_str, start_pos);
        if (end_pos == std::string::npos) break;
        
        std::string student_block = xml_data.substr(start_pos, end_pos - start_pos);
        student_blocks.push_back(student_block);
        
        pos = end_pos + end_str.length();
    }
    
    // Search for matching student
    for (const auto& block : student_blocks) {
        std::string block_username = extract_tag_content(block, "username");
        std::string block_password = extract_tag_content(block, "password");
        
        // Trim whitespace from extracted values
        auto trim = [](std::string& str) {
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), str.end());
        };
        
        trim(block_username);
        trim(block_password);
        
        if (block_username == username && block_password == password) {
            // Extract student information
            std::string name = extract_tag_content(block, "name");
            std::string citizenship = extract_tag_content(block, "citizenship");
            std::string age = extract_tag_content(block, "age");
            
            trim(name);
            trim(citizenship);
            trim(age);
            
            // Populate result map
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            return result;
        }
    }
    
    // Return empty map if no match found
    return result;
}