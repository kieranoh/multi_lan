#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Construir o caminho completo do arquivo
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Verificar se o arquivo existe e é um arquivo regular
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Abrir o arquivo em modo binário para preservar todos os caracteres
        std::ifstream file(file_path, std::ios::binary);
        
        // Verificar se o arquivo foi aberto com sucesso
        if (!file.is_open()) {
            return "";
        }
        
        // Ler o conteúdo do arquivo
        std::string content;
        file.seekg(0, std::ios::end);
        content.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&content[0], content.size());
        
        // Verificar se a leitura foi bem-sucedida
        if (!file) {
            return "";
        }
        
        return content;
    }
    catch (const std::exception&) {
        // Capturar qualquer exceção (erros de permissão, etc.) e retornar string vazia
        return "";
    }
}