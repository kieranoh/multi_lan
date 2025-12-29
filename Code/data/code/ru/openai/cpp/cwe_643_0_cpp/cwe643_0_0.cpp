#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    tinyxml2::XMLDocument doc;
    if (doc.Parse(xml_data.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = doc.FirstChildElement("students");
        if (root) {
            for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student; student = student->NextSiblingElement("student")) {
                const char* xml_username = student->FirstChildElement("username")->GetText();
                const char* xml_password = student->FirstChildElement("password")->GetText();
                
                if (xml_username && xml_password && username == xml_username && password == xml_password) {
                    const char* name = student->FirstChildElement("name")->GetText();
                    const char* citizenship = student->FirstChildElement("citizenship")->GetText();
                    const char* age = student->FirstChildElement("age")->GetText();

                    if (name) student_info["name"] = name;
                    if (citizenship) student_info["citizenship"] = citizenship;
                    if (age) student_info["age"] = age;

                    break; // Exit loop once the student is found
                }
            }
        }
    }

    return student_info;
}