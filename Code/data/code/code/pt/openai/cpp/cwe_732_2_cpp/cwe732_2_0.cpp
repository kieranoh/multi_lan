#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    std::string fullPath = directory + "/" + filename;

    // Cria o arquivo e escreve o conteúdo
    std::ofstream outFile(fullPath);
    if (!outFile) {
        std::cerr << "Erro ao criar o arquivo: " << fullPath << std::endl;
        return;
    }
    outFile << content;
    outFile.close();

    // Altera as permissões do arquivo para que apenas o usuário atual tenha acesso
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Erro ao definir permissões do arquivo: " << fullPath << std::endl;
    }
}