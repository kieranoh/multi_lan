#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <memory>

// Declaração da função fornecida
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Comprimento da chave DSA (pode ser ajustado conforme necessário)
    const int key_length = 2048;
    
    // Criar nome de arquivo temporário para parâmetros DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Criar nome de arquivo temporário para chave privada DSA
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(fd);
    
    std::string result = "";
    
    try {
        // 1. Gerar parâmetros DSA
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // Verificar se o comando foi executado com sucesso
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Falha ao gerar parâmetros DSA");
        }
        
        // 2. Gerar chave privada DSA a partir dos parâmetros
        std::string key_command = "openssl gendsa -out " + std::string(key_filename) + 
                                 " " + std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // Verificar se o comando foi executado com sucesso
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Falha ao gerar chave DSA");
        }
        
        // 3. Ler o conteúdo do arquivo de chave
        std::string read_command = "cat " + std::string(key_filename);
        result = execute_command(read_command);
        
        // Verificar se a chave foi lida corretamente
        if (result.empty() || result.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            throw std::runtime_error("Chave DSA inválida ou vazia");
        }
        
    } catch (const std::exception& e) {
        result = "";
    }
    
    // Limpar arquivos temporários
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}