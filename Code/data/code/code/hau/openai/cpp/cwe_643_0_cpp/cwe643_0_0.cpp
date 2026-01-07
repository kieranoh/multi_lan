#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h> // Ensure you have tinyxml2 library installed

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    tinyxml2::XMLDocument doc;
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Return empty map on parse failure
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (root == nullptr) {
        return student_info; // Return empty map if no root element
    }

    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username") ? student->FirstChildElement("username")->GetText() : nullptr;
        const char* pass = student->FirstChildElement("password") ? student->FirstChildElement("password")->GetText() : nullptr;

        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name") ? student->FirstChildElement("name")->GetText() : nullptr;
            const char* citizenship = student->FirstChildElement("citizenship") ? student->FirstChildElement("citizenship")->GetText() : nullptr;
            const char* age = student->FirstChildElement("age") ? student->FirstChildElement("age")->GetText() : nullptr;

            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            break; // Exit loop after finding the student
        }
    }

    return student_info; // Return the found student info or empty map
}