#include <string>
#include <map>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Guardar una copia del encabezado original en caso de error
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convertir el tipo de información a minúsculas para comparación insensible a mayúsculas
        std::string lower_type = info_type;
        std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(), ::tolower);
        
        // Determinar la clave del encabezado basada en el tipo de información
        std::string header_key;
        
        if (lower_type == "lang") {
            header_key = "Accept-Language";
        } else if (lower_type == "encoding") {
            header_key = "Accept-Encoding";
        } else if (lower_type == "cache") {
            header_key = "Cache-Control";
        } else {
            // Tipo de información no válido, restaurar encabezado original
            header = original_header;
            return;
        }
        
        // Verificar que el contenido de la información no esté vacío
        if (info_content.empty()) {
            header = original_header;
            return;
        }
        
        // Almacenar la información en el encabezado
        header[header_key] = info_content;
        
    } catch (...) {
        // En caso de cualquier excepción, restaurar el encabezado original
        header = original_header;
    }
}