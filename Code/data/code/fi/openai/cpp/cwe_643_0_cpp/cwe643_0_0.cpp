#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    tinyxml2::XMLDocument doc;
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Palautetaan tyhjää karttaa, jos XML ei ole voimassa
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (root == nullptr) {
        return student_info; // Palautetaan tyhjää karttaa, jos juurielementti puuttuu
    }

    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // Tarkistetaan käyttäjänimi ja salasana
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            // Lisätään opiskelijatiedot karttaan
            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            return student_info; // Palautetaan löydetyt tiedot
        }
    }

    return student_info; // Palautetaan tyhjää karttaa, jos ei löytynyt
}