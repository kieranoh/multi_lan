#include <string>
#include <iostream>

bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Utiliza a função find da string para buscar o padrão no conteúdo
        return content.find(pattern) != std::string::npos;
    } catch (...) {
        // Retorna falso se algo der errado
        return false;
    }
}