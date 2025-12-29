#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>
#include <cstdio>

std::string create_private_key() {
    const int key_length = 2048; // RSA anahtar uzunluğu
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Komutun çalıştırılması için bir benzersiz dosya oluşturuyoruz
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Komut çalıştırılamadıysa NULL döndür
    }
    
    char buffer[128];
    std::string result;
    
    // Komut çıktısını okuyarak result değişkenine ekliyoruz
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    // Eğer anahtar oluşturulamadıysa NULL döndür
    if (result.empty()) {
        return nullptr;
    }
    
    return result;
}