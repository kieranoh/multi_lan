#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// Forward declarations for pugixml
namespace pugi {
    class xml_document;
    class xml_node;
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Include pugixml implementation
    // Since we cannot include external headers directly, we'll implement a simple XML parser
    // that works for the specific structure shown in the docstring
    
    // Simple XML parsing for the specific structure
    size_t pos = 0;
    std::string search_str = "<student>";
    
    while ((pos = xml_data.find(search_str, pos)) != std::string::npos) {
        size_t student_start = pos;
        size_t student_end = xml_data.find("</student>", pos);
        
        if (student_end == std::string::npos) {
            break;
        }
        
        // Extract student block
        std::string student_block = xml_data.substr(student_start, student_end - student_start + 10);
        
        // Helper function to extract value between tags
        auto extract_value = [&](const std::string& tag) -> std::string {
            std::string open_tag = "<" + tag + ">";
            std::string close_tag = "</" + tag + ">";
            
            size_t start = student_block.find(open_tag);
            if (start == std::string::npos) return "";
            
            start += open_tag.length();
            size_t end = student_block.find(close_tag, start);
            if (end == std::string::npos) return "";
            
            return student_block.substr(start, end - start);
        };
        
        // Extract username and password from student block
        std::string student_username = extract_value("username");
        std::string student_password = extract_value("password");
        
        // Check if this is the student we're looking for
        if (student_username == username && student_password == password) {
            // Extract the required information
            std::string name = extract_value("name");
            std::string citizenship = extract_value("citizenship");
            std::string age = extract_value("age");
            
            // Populate the result map
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            // Found the student, return immediately
            return result;
        }
        
        // Move to next student
        pos = student_end + 10;
    }
    
    // Return empty map if student not found
    return result;
}