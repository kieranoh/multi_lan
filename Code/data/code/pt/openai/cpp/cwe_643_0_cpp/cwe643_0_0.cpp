#include <string>
#include <map>
#include <iostream>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // Carregar os dados XML
    if (doc.Parse(xml_data.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = doc.FirstChildElement("students");
        if (root) {
            for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student; student = student->NextSiblingElement("student")) {
                const char* user = student->FirstChildElement("username")->GetText();
                const char* pass = student->FirstChildElement("password")->GetText();
                const char* name = student->FirstChildElement("name")->GetText();
                const char* citizenship = student->FirstChildElement("citizenship")->GetText();
                const char* age = student->FirstChildElement("age")->GetText();

                if (user && pass && username == user && password == pass) {
                    student_info["name"] = name ? name : "";
                    student_info["citizenship"] = citizenship ? citizenship : "";
                    student_info["age"] = age ? age : "";
                    break; // Encontrado, não é necessário continuar
                }
            }
        }
    }

    return student_info;
}