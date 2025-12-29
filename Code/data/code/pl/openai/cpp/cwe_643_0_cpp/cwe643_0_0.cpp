#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_data.c_str());

    std::map<std::string, std::string> student_info;

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (root) {
        for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
            const char* user = student->FirstChildElement("username")->GetText();
            const char* pass = student->FirstChildElement("password")->GetText();

            if (user && pass && username == user && password == pass) {
                student_info["name"] = student->FirstChildElement("name")->GetText() ? student->FirstChildElement("name")->GetText() : "";
                student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText() ? student->FirstChildElement("citizenship")->GetText() : "";
                student_info["age"] = student->FirstChildElement("age")->GetText() ? student->FirstChildElement("age")->GetText() : "";
                break;
            }
        }
    }

    return student_info;
}