#include <string>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

// Função fornecida para executar um comando shell e capturar sua saída
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Criar um arquivo temporário para armazenar os parâmetros DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Retorna uma string vazia em caso de erro
    }
    close(fd); // Fecha o descritor de arquivo, pois já não é mais necessário

    // Passo 1: Gerar parâmetros DSA
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command).empty()) {
        remove(param_filename); // Remove o arquivo temporário em caso de erro
        return ""; // Retorna uma string vazia em caso de erro
    }

    // Passo 2: Gerar a chave DSA
    std::string key_command = "openssl gendsa -out /tmp/dsa_private.pem " + std::string(param_filename);
    if (execute_command(key_command).empty()) {
        remove(param_filename); // Remove o arquivo temporário em caso de erro
        return ""; // Retorna uma string vazia em caso de erro
    }

    // Ler a chave DSA gerada
    std::string key_path = "/tmp/dsa_private.pem";
    std::string private_key = execute_command("cat " + key_path);

    // Limpar arquivos temporários
    remove(param_filename);
    remove(key_path.c_str());

    return private_key; // Retorna a chave DSA privada em formato PEM
}