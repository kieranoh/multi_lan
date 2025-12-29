#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // Carica i dati XML
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Restituisce una mappa vuota in caso di errore
    }

    // Trova il nodo students
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        return student_info; // Restituisce una mappa vuota se non trovato
    }

    // Itera attraverso gli studenti
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* xml_username = student->FirstChildElement("username")->GetText();
        const char* xml_password = student->FirstChildElement("password")->GetText();
        
        // Verifica se il nome utente e la password corrispondono
        if (xml_username && xml_password && username == xml_username && password == xml_password) {
            student_info["name"] = student->FirstChildElement("name")->GetText();
            student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText();
            student_info["age"] = student->FirstChildElement("age")->GetText();
            break; // Trovato lo studente, esci dal ciclo
        }
    }

    return student_info; // Restituisce le informazioni dello studente o una mappa vuota se non trovato
}