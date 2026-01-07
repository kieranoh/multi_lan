#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Return empty map if XML parsing fails
    }

    tinyxml2::XMLElement* students = doc.FirstChildElement("students");
    if (students == nullptr) {
        return student_info; // Return empty map if no students element
    }

    for (tinyxml2::XMLElement* student = students->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user_elem = student->FirstChildElement("username")->GetText();
        const char* pass_elem = student->FirstChildElement("password")->GetText();
        
        if (user_elem && pass_elem && username == user_elem && password == pass_elem) {
            const char* name_elem = student->FirstChildElement("name")->GetText();
            const char* citizenship_elem = student->FirstChildElement("citizenship")->GetText();
            const char* age_elem = student->FirstChildElement("age")->GetText();

            if (name_elem && citizenship_elem && age_elem) {
                student_info["name"] = name_elem;
                student_info["citizenship"] = citizenship_elem;
                student_info["age"] = age_elem;
            }
            break; // Stop searching after finding the student
        }
    }

    return student_info; // Return student info or empty map if not found
}