#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Construir o comando com o diretório fornecido
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Buffer para armazenar a saída
    std::array<char, 128> buffer;
    std::string result;
    
    // Abrir o pipe para leitura da saída do comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Falha ao abrir o pipe
        return "";
    }
    
    // Ler a saída do comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verificar se houve erro na execução do comando (resultado vazio pode indicar erro)
    // O comando redireciona stderr para /dev/null, então se result estiver vazio,
    // provavelmente o diretório não existe ou não tem permissão
    if (result.empty()) {
        return "";
    }
    
    return result;
}