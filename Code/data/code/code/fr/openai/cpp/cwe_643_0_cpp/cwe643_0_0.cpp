#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // Charger les données XML
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Retourner une carte vide en cas d'erreur de parsing
    }

    // Trouver l'élément 'students'
    tinyxml2::XMLElement* students = doc.FirstChildElement("students");
    if (students == nullptr) {
        return student_info; // Retourner une carte vide si l'élément 'students' n'existe pas
    }

    // Parcourir les étudiants
    for (tinyxml2::XMLElement* student = students->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // Vérifier si le nom d'utilisateur et le mot de passe correspondent
        if (user != nullptr && pass != nullptr && username == user && password == pass) {
            student_info["name"] = student->FirstChildElement("name")->GetText() ? student->FirstChildElement("name")->GetText() : "";
            student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText() ? student->FirstChildElement("citizenship")->GetText() : "";
            student_info["age"] = student->FirstChildElement("age")->GetText() ? student->FirstChildElement("age")->GetText() : "";
            break; // Sortir de la boucle une fois l'étudiant trouvé
        }
    }

    return student_info; // Retourner les informations de l'étudiant ou une carte vide si non trouvé
}