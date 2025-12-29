#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Guardar el header original en caso de error
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convertir info_type a minúsculas para comparación insensible a mayúsculas/minúsculas
        std::string type_lower = info_type;
        std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(), ::tolower);
        
        // Determinar la clave del header basada en el tipo de información
        std::string header_key;
        
        if (type_lower == "lang") {
            header_key = "Accept-Language";
        } else if (type_lower == "encoding") {
            header_key = "Accept-Encoding";
        } else if (type_lower == "cache") {
            header_key = "Cache-Control";
        } else {
            // Tipo de información no válido, restaurar header original
            header = original_header;
            return;
        }
        
        // Verificar que el contenido no esté vacío
        if (info_content.empty()) {
            header = original_header;
            return;
        }
        
        // Almacenar la información en el header
        header[header_key] = info_content;
        
    } catch (...) {
        // Cualquier excepción, restaurar el header original
        header = original_header;
    }
}