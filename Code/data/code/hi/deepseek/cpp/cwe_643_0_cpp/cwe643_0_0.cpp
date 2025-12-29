#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML पार्सिंग के लिए सरल दृष्टिकोण
    std::vector<std::string> students;
    std::string data = xml_data;
    
    // <student> टैग्स को खोजें
    size_t pos = 0;
    while ((pos = data.find("<student>", pos)) != std::string::npos) {
        size_t end_pos = data.find("</student>", pos);
        if (end_pos == std::string::npos) break;
        
        std::string student_xml = data.substr(pos, end_pos - pos + 10);
        students.push_back(student_xml);
        pos = end_pos + 10;
    }
    
    // प्रत्येक छात्र के XML को प्रोसेस करें
    for (const auto& student_xml : students) {
        std::string current_username, current_password, name, citizenship, age;
        
        // उपयोगकर्ता नाम निकालें
        size_t user_start = student_xml.find("<username>");
        size_t user_end = student_xml.find("</username>");
        if (user_start != std::string::npos && user_end != std::string::npos) {
            current_username = student_xml.substr(user_start + 10, user_end - (user_start + 10));
        }
        
        // पासवर्ड निकालें
        size_t pass_start = student_xml.find("<password>");
        size_t pass_end = student_xml.find("</password>");
        if (pass_start != std::string::npos && pass_end != std::string::npos) {
            current_password = student_xml.substr(pass_start + 10, pass_end - (pass_start + 10));
        }
        
        // यदि उपयोगकर्ता नाम और पासवर्ड मेल खाते हैं
        if (current_username == username && current_password == password) {
            // नाम निकालें
            size_t name_start = student_xml.find("<name>");
            size_t name_end = student_xml.find("</name>");
            if (name_start != std::string::npos && name_end != std::string::npos) {
                name = student_xml.substr(name_start + 6, name_end - (name_start + 6));
            }
            
            // नागरिकता निकालें
            size_t cit_start = student_xml.find("<citizenship>");
            size_t cit_end = student_xml.find("</citizenship>");
            if (cit_start != std::string::npos && cit_end != std::string::npos) {
                citizenship = student_xml.substr(cit_start + 13, cit_end - (cit_start + 13));
            }
            
            // उम्र निकालें
            size_t age_start = student_xml.find("<age>");
            size_t age_end = student_xml.find("</age>");
            if (age_start != std::string::npos && age_end != std::string::npos) {
                age = student_xml.substr(age_start + 5, age_end - (age_start + 5));
            }
            
            // परिणाम मानचित्र भरें
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            // मिल गया, लूप से बाहर निकलें
            break;
        }
    }
    
    return result;
}