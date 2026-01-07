#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // XML datua kargatu
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Parseatzean errorea badago, mapa huts itzuli.
    }

    // XPath kontsultak egiteko ikaslea bilatu
    tinyxml2::XMLElement* student = doc.FirstChildElement("students")->FirstChildElement("student");
    
    while (student) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();

        // Erabiltzaile izena eta pasahitza egiaztatu
        if (user && pass && username == user && password == pass) {
            student_info["name"] = student->FirstChildElement("name")->GetText();
            student_info["age"] = student->FirstChildElement("age")->GetText();
            student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText();
            break; // Ikaslea aurkitu dugu, irten.
        }

        student = student->NextSiblingElement("student");
    }

    return student_info; // Aurkitutako ikaslearen informazioa itzuli.
}