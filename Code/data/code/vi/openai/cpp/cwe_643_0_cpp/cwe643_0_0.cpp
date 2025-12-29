#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // Load the XML data
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Return empty map if parsing fails
    }

    // Find the students element
    tinyxml2::XMLElement* students = doc.FirstChildElement("students");
    if (students == nullptr) {
        return student_info; // Return empty map if no students found
    }

    // Iterate through each student
    for (tinyxml2::XMLElement* student = students->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // Check if the username and password match
        if (user != nullptr && pass != nullptr && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            // Populate the student_info map
            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            break; // Exit loop after finding the student
        }
    }

    return student_info; // Return the student info map (may be empty)
}