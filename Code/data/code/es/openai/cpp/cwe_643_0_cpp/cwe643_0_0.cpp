#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // Cargar los datos XML en el documento
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // Retornar mapa vacío en caso de error de análisis
    }

    // Buscar todos los nodos de estudiante
    tinyxml2::XMLElement* student = doc.FirstChildElement("students")->FirstChildElement("student");
    while (student) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // Verificar si el nombre de usuario y la contraseña coinciden
        if (user && pass && username == user && password == pass) {
            const char* name = student->FirstChildElement("name")->GetText();
            const char* citizenship = student->FirstChildElement("citizenship")->GetText();
            const char* age = student->FirstChildElement("age")->GetText();

            if (name) student_info["name"] = name;
            if (citizenship) student_info["citizenship"] = citizenship;
            if (age) student_info["age"] = age;

            break; // Salir después de encontrar el estudiante
        }
        student = student->NextSiblingElement("student"); // Continuar con el siguiente estudiante
    }

    return student_info; // Retornar información del estudiante o mapa vacío
}