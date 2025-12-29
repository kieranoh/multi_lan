#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file) {
        return ""; // Retorna string vazia em caso de erro
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Adiciona cada linha ao conteúdo
    }

    file.close();
    return content; // Retorna o conteúdo lido
}