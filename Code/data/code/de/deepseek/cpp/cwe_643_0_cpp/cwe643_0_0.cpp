#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Find all student blocks
    std::vector<std::string> student_blocks;
    std::size_t start_pos = 0;
    const std::string start_tag = "<student>";
    const std::string end_tag = "</student>";
    
    while (true) {
        std::size_t student_start = xml_data.find(start_tag, start_pos);
        if (student_start == std::string::npos) break;
        
        std::size_t student_end = xml_data.find(end_tag, student_start);
        if (student_end == std::string::npos) break;
        
        student_end += end_tag.length();
        student_blocks.push_back(xml_data.substr(student_start, student_end - student_start));
        start_pos = student_end;
    }
    
    // Helper function to extract content from XML tag
    auto extract_tag_content = [](const std::string& block, const std::string& tag_name) -> std::string {
        std::string start_tag = "<" + tag_name + ">";
        std::string end_tag = "</" + tag_name + ">";
        
        std::size_t start_pos = block.find(start_tag);
        if (start_pos == std::string::npos) return "";
        
        start_pos += start_tag.length();
        std::size_t end_pos = block.find(end_tag, start_pos);
        if (end_pos == std::string::npos) return "";
        
        return block.substr(start_pos, end_pos - start_pos);
    };
    
    // Search for matching student
    for (const auto& block : student_blocks) {
        std::string block_username = extract_tag_content(block, "username");
        std::string block_password = extract_tag_content(block, "password");
        
        // Trim whitespace if any
        block_username.erase(std::remove_if(block_username.begin(), block_username.end(), ::isspace), block_username.end());
        block_password.erase(std::remove_if(block_password.begin(), block_password.end(), ::isspace), block_password.end());
        
        if (block_username == username && block_password == password) {
            // Extract student info
            std::string name = extract_tag_content(block, "name");
            std::string citizenship = extract_tag_content(block, "citizenship");
            std::string age = extract_tag_content(block, "age");
            
            // Trim whitespace from extracted values
            auto trim = [](std::string& str) {
                str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }));
                str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }).base(), str.end());
            };
            
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