#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // Load the XML data
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Return empty map on parsing error
    }

    // Find the root element
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        return student_info; // Return empty map if no students element found
    }

    // Iterate over each student element
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user_elem = student->FirstChildElement("username")->GetText();
        const char* pass_elem = student->FirstChildElement("password")->GetText();

        // Check if the username and password match
        if (user_elem && pass_elem && username == user_elem && password == pass_elem) {
            // Retrieve student information
            const char* name_elem = student->FirstChildElement("name")->GetText();
            const char* citizenship_elem = student->FirstChildElement("citizenship")->GetText();
            const char* age_elem = student->FirstChildElement("age")->GetText();

            // Populate the map with student info
            if (name_elem) student_info["name"] = name_elem;
            if (citizenship_elem) student_info["citizenship"] = citizenship_elem;
            if (age_elem) student_info["age"] = age_elem;

            break; // Exit the loop after finding the matching student
        }
    }

    return student_info; // Return the student info map (can be empty if not found)
}