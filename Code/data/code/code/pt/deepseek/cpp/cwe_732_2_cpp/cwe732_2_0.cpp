#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Verificar se o diretório existe, caso contrário, criá-lo
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // Construir o caminho completo do arquivo
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Salvar o conteúdo no arquivo
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + filePath.string());
    }
    file.write(content.c_str(), content.size());
    file.close();

    // Definir permissões para que apenas o usuário atual tenha acesso (leitura/escrita)
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Falha ao definir permissões do arquivo: " + filePath.string());
    }
}