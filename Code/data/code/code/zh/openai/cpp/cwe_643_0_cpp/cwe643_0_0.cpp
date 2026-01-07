#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

// 解析 XML 数据并返回给定用户名和密码的学生信息。
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // 加载 XML 数据
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // 返回空映射
    }

    // 查找学生节点
    tinyxml2::XMLElement* student = doc.FirstChildElement("students")->FirstChildElement("student");
    while (student) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();

        // 检查用户名和密码是否匹配
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            // 存储学生信息
            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            return student_info; // 找到后返回映射
        }
        student = student->NextSiblingElement("student");
    }

    return student_info; // 没有找到，返回空映射
}