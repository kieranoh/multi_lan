#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Verificar se o padrão ou conteúdo são vazios
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    try {
        // Verificar se o padrão contém caracteres especiais de regex
        // Se contiver, tratar como expressão regular
        bool hasSpecialChars = false;
        const std::string specialChars = ".*+?^${}()|[]\\";
        
        for (char c : pattern) {
            if (specialChars.find(c) != std::string::npos) {
                hasSpecialChars = true;
                break;
            }
        }
        
        if (hasSpecialChars) {
            // Tentar compilar e usar como regex
            std::regex regexPattern;
            try {
                regexPattern = std::regex(pattern);
            } catch (const std::regex_error& e) {
                // Padrão de regex inválido
                return false;
            }
            
            return std::regex_search(content, regexPattern);
        } else {
            // Busca simples de substring
            return content.find(pattern) != std::string::npos;
        }
    } catch (...) {
        // Capturar qualquer exceção inesperada
        return false;
    }
}