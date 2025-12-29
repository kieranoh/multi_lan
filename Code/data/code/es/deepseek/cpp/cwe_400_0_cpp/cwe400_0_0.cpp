#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Verificar si el patrón está vacío - un patrón vacío siempre se encuentra
    if (pattern.empty()) {
        return true;
    }
    
    // Verificar si el contenido está vacío - no se puede encontrar un patrón no vacío en contenido vacío
    if (content.empty()) {
        return false;
    }
    
    try {
        // Usar búsqueda de subcadena simple primero para casos básicos
        // Esto es más eficiente que regex para patrones simples
        if (pattern.find_first_of(".*+?^${}()|[]\\") == std::string::npos) {
            // No contiene caracteres especiales de regex, usar búsqueda simple
            return content.find(pattern) != std::string::npos;
        }
        
        // Intentar usar regex para patrones más complejos
        // Escapar caracteres especiales de regex si es necesario
        std::regex regex_pattern;
        
        // Intentar compilar el patrón como regex
        // Usar ECMAScript (por defecto) que es el estándar más común
        regex_pattern = std::regex(pattern, std::regex::ECMAScript | std::regex::optimize);
        
        // Buscar el patrón en el contenido
        return std::regex_search(content, regex_pattern);
        
    } catch (const std::regex_error& e) {
        // Si el patrón no es un regex válido, intentar búsqueda literal
        // Esto maneja casos donde el usuario ingresa caracteres especiales de regex
        // pero no pretende que sean un patrón regex
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // Capturar cualquier otra excepción y devolver falso
        return false;
    }
}