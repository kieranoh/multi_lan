#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include <algorithm>

// Forward declarations for pugixml
namespace pugi {
    class xml_document;
    class xml_node;
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Check if pugixml is available at compile time
    #ifdef HAS_PUGIXML
    try {
        // Create XML document
        pugi::xml_document doc;
        
        // Load XML data
        pugi::xml_parse_result parse_result = doc.load_string(xml_data.c_str());
        
        if (!parse_result) {
            // Parsing failed, return empty map
            return result;
        }
        
        // XPath query to find student with matching username and password
        std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
        
        // Execute XPath query
        pugi::xpath_node_set students = doc.select_nodes(xpath_query.c_str());
        
        // Check if we found exactly one student
        if (students.size() == 1) {
            pugi::xml_node student_node = students[0].node();
            
            // Extract information
            pugi::xml_node name_node = student_node.child("name");
            pugi::xml_node citizenship_node = student_node.child("citizenship");
            pugi::xml_node age_node = student_node.child("age");
            
            if (name_node && citizenship_node && age_node) {
                result["name"] = name_node.text().get();
                result["citizenship"] = citizenship_node.text().get();
                result["age"] = age_node.text().get();
            }
        }
        // If no student found or multiple found (shouldn't happen with unique usernames), return empty map
        
    } catch (...) {
        // Any exception, return empty map
        return result;
    }
    
    #else
    // Fallback implementation without pugixml
    // Simple XML parsing for the specific structure
    
    std::string search_pattern = "<student>";
    std::vector<std::string> students;
    size_t pos = 0;
    
    // Split XML into individual student sections
    while ((pos = xml_data.find(search_pattern, pos)) != std::string::npos) {
        size_t end_pos = xml_data.find("</student>", pos);
        if (end_pos == std::string::npos) {
            break;
        }
        
        std::string student_xml = xml_data.substr(pos, end_pos - pos + 10); // +10 for "</student>"
        students.push_back(student_xml);
        pos = end_pos + 10;
    }
    
    // Helper function to extract value from XML tag
    auto extract_value = [](const std::string& xml, const std::string& tag) -> std::string {
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
        return xml.substr(start_pos, end_pos - start_pos);
    };
    
    // Search for matching student
    for (const auto& student_xml : students) {
        std::string student_username = extract_value(student_xml, "username");
        std::string student_password = extract_value(student_xml, "password");
        
        // Trim whitespace if any
        student_username.erase(std::remove(student_username.begin(), student_username.end(), '\n'), student_username.end());
        student_username.erase(std::remove(student_username.begin(), student_username.end(), '\r'), student_username.end());
        student_username.erase(std::remove(student_username.begin(), student_username.end(), ' '), student_username.end());
        
        student_password.erase(std::remove(student_password.begin(), student_password.end(), '\n'), student_password.end());
        student_password.erase(std::remove(student_password.begin(), student_password.end(), '\r'), student_password.end());
        student_password.erase(std::remove(student_password.begin(), student_password.end(), ' '), student_password.end());
        
        if (student_username == username && student_password == password) {
            std::string name = extract_value(student_xml, "name");
            std::string citizenship = extract_value(student_xml, "citizenship");
            std::string age = extract_value(student_xml, "age");
            
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
            
            if (!name.empty() && !citizenship.empty() && !age.empty()) {
                result["name"] = name;
                result["citizenship"] = citizenship;
                result["age"] = age;
            }
            break;
        }
    }
    #endif
    
    return result;
}