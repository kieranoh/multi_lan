#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>

// TinyXML2 egy könnyű, hatékony XML parser
#include "tinyxml2.h"

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    using namespace tinyxml2;
    std::map<std::string, std::string> result;
    
    // XML dokumentum létrehozása
    XMLDocument doc;
    
    // XML adatok betöltése a stringből
    if (doc.Parse(xml_data.c_str()) != XML_SUCCESS) {
        // Ha a parsing sikertelen, üres térképpel térünk vissza
        return result;
    }
    
    // Gyökérelem lekérése
    XMLElement* root = doc.RootElement();
    if (!root) {
        return result;
    }
    
    // Minden student elem bejárása
    for (XMLElement* student = root->FirstChildElement("student"); 
         student != nullptr; 
         student = student->NextSiblingElement("student")) {
        
        // Felhasználónév és jelszó lekérése
        XMLElement* usernameElem = student->FirstChildElement("username");
        XMLElement* passwordElem = student->FirstChildElement("password");
        
        if (!usernameElem || !passwordElem) {
            continue; // Ha nincs username vagy password elem, tovább lépünk
        }
        
        const char* storedUsername = usernameElem->GetText();
        const char* storedPassword = passwordElem->GetText();
        
        // Ha nincs szöveg, tovább lépünk
        if (!storedUsername || !storedPassword) {
            continue;
        }
        
        // Ellenőrizzük a felhasználónevet és jelszót
        if (username == storedUsername && password == storedPassword) {
            // További adatok lekérése
            XMLElement* nameElem = student->FirstChildElement("name");
            XMLElement* citizenshipElem = student->FirstChildElement("citizenship");
            XMLElement* ageElem = student->FirstChildElement("age");
            
            // Ha minden szükséges adat megtalálható, feltöltjük a térképet
            if (nameElem && citizenshipElem && ageElem) {
                const char* name = nameElem->GetText();
                const char* citizenship = citizenshipElem->GetText();
                const char* age = ageElem->GetText();
                
                if (name && citizenship && age) {
                    result["name"] = name;
                    result["citizenship"] = citizenship;
                    result["age"] = age;
                }
            }
            // Ha megtaláltuk a diákot, kilépünk a ciklusból
            break;
        }
    }
    
    return result;
}