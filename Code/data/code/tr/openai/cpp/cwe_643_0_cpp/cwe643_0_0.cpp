#include <string>
#include <map>
#include <iostream>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // XML verisini yükle
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Hata durumunda boş harita döndür
    }

    // Öğrenci öğelerini al
    tinyxml2::XMLElement* student = doc.FirstChildElement("students")->FirstChildElement("student");
    while (student) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();

        // Kullanıcı adı ve şifre kontrolü
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            // Bilgileri haritaya ekle
            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;
            break; // Öğrenci bulundu, döngüden çık
        }
        student = student->NextSiblingElement("student");
    }

    return student_info; // Öğrenci bilgilerini döndür
}