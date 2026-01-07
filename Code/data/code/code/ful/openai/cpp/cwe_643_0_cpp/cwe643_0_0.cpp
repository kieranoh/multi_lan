#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    tinyxml2::XMLDocument doc;
    if (doc.Parse(xml_data.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* students = doc.FirstChildElement("students");
        for (tinyxml2::XMLElement* student = students->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
            const char* user = student->FirstChildElement("username")->GetText();
            const char* pass = student->FirstChildElement("password")->GetText();
            if (user && pass && username == user && password == pass) {
                const char* name = student->FirstChildElement("name")->GetText();
                const char* citizenship = student->FirstChildElement("citizenship")->GetText();
                const char* age = student->FirstChildElement("age")->GetText();

                if (name) student_info["name"] = name;
                if (citizenship) student_info["citizenship"] = citizenship;
                if (age) student_info["age"] = age;
                break; // 학생을 찾았으므로 루프를 종료합니다.
            }
        }
    }
    
    return student_info;
}