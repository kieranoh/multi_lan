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
                const char* name = student->FirstChildElement("name")->GetText();
                const char* citizenship = student->FirstChildElement("citizenship")->GetText();
                const char* age = student->FirstChildElement("age")->GetText();

                if (name && citizenship && age) {
                    student_info["name"] = name;
                    student_info["citizenship"] = citizenship;
                    student_info["age"] = age;
                }
                break; // Found the student, no need to continue
            }
        }
    }

    return student_info;
}