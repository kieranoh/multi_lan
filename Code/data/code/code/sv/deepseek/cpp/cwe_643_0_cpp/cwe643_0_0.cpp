#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

// Helper function to trim whitespace from both ends of a string
static inline std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        ++start;
    }
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    return std::string(start, end + 1);
}

// Helper function to extract content between XML tags
static std::string extract_xml_content(const std::string& xml, const std::string& tag) {
    std::string open_tag = "<" + tag + ">";
    std::string close_tag = "</" + tag + ">";
    
    size_t start_pos = xml.find(open_tag);
    if (start_pos == std::string::npos) {
        return "";
    }
    
    size_t end_pos = xml.find(close_tag, start_pos);
    if (end_pos == std::string::npos) {
        return "";
    }
    
    start_pos += open_tag.length();
    return trim(xml.substr(start_pos, end_pos - start_pos));
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Find all student entries
    std::string student_tag = "<student>";
    std::string end_student_tag = "</student>";
    
    size_t pos = 0;
    while (pos < xml_data.length()) {
        // Find the next student block
        size_t student_start = xml_data.find(student_tag, pos);
        if (student_start == std::string::npos) {
            break;
        }
        
        size_t student_end = xml_data.find(end_student_tag, student_start);
        if (student_end == std::string::npos) {
            break;
        }
        
        // Extract the student block
        student_start += student_tag.length();
        std::string student_block = xml_data.substr(student_start, student_end - student_start);
        
        // Extract username and password from the student block
        std::string student_username = extract_xml_content(student_block, "username");
        std::string student_password = extract_xml_content(student_block, "password");
        
        // Check if this is the student we're looking for
        if (student_username == username && student_password == password) {
            // Extract the other information
            std::string name = extract_xml_content(student_block, "name");
            std::string citizenship = extract_xml_content(student_block, "citizenship");
            std::string age = extract_xml_content(student_block, "age");
            
            // Populate the result map
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            // Found the student, return immediately
            return result;
        }
        
        // Move to the next student
        pos = student_end + end_student_tag.length();
    }
    
    // Return empty map if student not found
    return result;
}