#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file");
    }
    close(fd);

    // DSA parametrelerini oluştur
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) != "") {
        remove(param_filename); // Temizle
        throw std::runtime_error("Failed to generate DSA parameters");
    }

    // DSA özel anahtarını oluştur
    std::string key_command = "openssl gendsa -out /tmp/dsa_private_key.pem -in " + std::string(param_filename);
    std::string result = execute_command(key_command);
    
    remove(param_filename); // Temizle

    if (result != "") {
        throw std::runtime_error("Failed to generate DSA private key");
    }

    // DSA özel anahtarını oku ve döndür
    std::string key_content = execute_command("cat /tmp/dsa_private_key.pem");
    remove("/tmp/dsa_private_key.pem"); // Temizle

    return key_content;
}