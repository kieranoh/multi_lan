#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // Carrega les dades XML
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Retorna un mapa buit si hi ha un error en la càrrega
    }

    // Obtenim l'arrel dels estudiants
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (root == nullptr) {
        return student_info; // Retorna un mapa buit si no s'ha trobat l'arrel
    }

    // Iterem per cada estudiant
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* xml_username = student->FirstChildElement("username")->GetText();
        const char* xml_password = student->FirstChildElement("password")->GetText();

        // Comprovem si el nom d'usuari i la contrasenya coincideixen
        if (xml_username && xml_password && username == xml_username && password == xml_password) {
            student_info["name"] = student->FirstChildElement("name")->GetText() ? student->FirstChildElement("name")->GetText() : "";
            student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText() ? student->FirstChildElement("citizenship")->GetText() : "";
            student_info["age"] = student->FirstChildElement("age")->GetText() ? student->FirstChildElement("age")->GetText() : "";
            break; // Aturem la cerca un cop trobem l'estudiant
        }
    }

    return student_info; // Retornem la informació de l'estudiant, o un mapa buit si no s'ha trobat
}