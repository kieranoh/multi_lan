#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Trobar l'inici de cada etiqueta <student>
    size_t pos = 0;
    while ((pos = xml_data.find("<student>", pos)) != std::string::npos) {
        size_t student_start = pos;
        size_t student_end = xml_data.find("</student>", pos);
        
        if (student_end == std::string::npos) {
            break;
        }
        
        // Extreure el bloc de l'estudiant
        std::string student_block = xml_data.substr(student_start, student_end - student_start + 10);
        
        // Funció per extreure el contingut d'una etiqueta
        auto extract_tag_content = [&](const std::string& tag_name) -> std::string {
            std::string open_tag = "<" + tag_name + ">";
            std::string close_tag = "</" + tag_name + ">";
            
            size_t start = student_block.find(open_tag);
            if (start == std::string::npos) {
                return "";
            }
            
            start += open_tag.length();
            size_t end = student_block.find(close_tag, start);
            if (end == std::string::npos) {
                return "";
            }
            
            return student_block.substr(start, end - start);
        };
        
        // Extreure les dades de l'estudiant
        std::string student_username = extract_tag_content("username");
        std::string student_password = extract_tag_content("password");
        
        // Verificar les credencials
        if (student_username == username && student_password == password) {
            result["name"] = extract_tag_content("name");
            result["citizenship"] = extract_tag_content("citizenship");
            result["age"] = extract_tag_content("age");
            return result;
        }
        
        // Moure la posició per a la propera cerca
        pos = student_end + 10;
    }
    
    // Retornar mapa buit si no es troba l'estudiant
    return result;
}