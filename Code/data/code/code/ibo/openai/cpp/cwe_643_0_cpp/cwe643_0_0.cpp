#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // Load the XML data
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Return empty map on parse failure
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (root == nullptr) {
        return student_info; // Return empty map if root is not found
    }

    // Iterate through each student element
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // Check if username and password match
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();
            
            // Populate the student_info map
            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            break; // Stop after finding the first match
        }
    }

    return student_info; // Return the populated map or an empty map
}