#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// TinyXML2 erabiliko dugu XML parseatzeko
#include "tinyxml2.h"

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML dokumentua parseatu
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError parseResult = doc.Parse(xml_data.c_str());
    
    // Parse errorea bada, mapa hutsa itzuli
    if (parseResult != tinyxml2::XML_SUCCESS) {
        return result;
    }
    
    // <students> elementua lortu
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        return result;
    }
    
    // <student> elementu bakoitza iteratu
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); 
         student != nullptr; 
         student = student->NextSiblingElement("student")) {
        
        // <username> eta <password> elementuak lortu
        tinyxml2::XMLElement* usernameElem = student->FirstChildElement("username");
        tinyxml2::XMLElement* passwordElem = student->FirstChildElement("password");
        
        // Balioak egiaztatu
        if (usernameElem && passwordElem) {
            std::string currentUsername = usernameElem->GetText() ? usernameElem->GetText() : "";
            std::string currentPassword = passwordElem->GetText() ? passwordElem->GetText() : "";
            
            // Erabiltzaile izena eta pasahitza egiaztatu
            if (currentUsername == username && currentPassword == password) {
                // Beste informazioa bilatu
                tinyxml2::XMLElement* nameElem = student->FirstChildElement("name");
                tinyxml2::XMLElement* citizenshipElem = student->FirstChildElement("citizenship");
                tinyxml2::XMLElement* ageElem = student->FirstChildElement("age");
                
                // Datuak mapara gehitu
                if (nameElem && nameElem->GetText()) {
                    result["name"] = nameElem->GetText();
                }
                if (citizenshipElem && citizenshipElem->GetText()) {
                    result["citizenship"] = citizenshipElem->GetText();
                }
                if (ageElem && ageElem->GetText()) {
                    result["age"] = ageElem->GetText();
                }
                
                // Ikaslea aurkitu da, bukatu
                return result;
            }
        }
    }
    
    // Ikaslea ez da aurkitu, mapa hutsa itzuli
    return result;
}