#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // Laad de XML-gegevens
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Retourneer lege map bij parsingfout
    }

    tinyxml2::XMLElement* students = doc.FirstChildElement("students");
    if (students == nullptr) {
        return student_info; // Retourneer lege map als er geen studenten zijn
    }

    for (tinyxml2::XMLElement* student = students->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();

        // Controleer gebruikersnaam en wachtwoord
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            // Vul de map met studenteninformatie
            if (name) student_info["name"] = name;
            if (age) student_info["age"] = age;
            if (citizenship) student_info["citizenship"] = citizenship;

            return student_info; // Retourneer informatie bij succesvolle match
        }
    }

    return student_info; // Retourneer lege map als geen match is gevonden
}