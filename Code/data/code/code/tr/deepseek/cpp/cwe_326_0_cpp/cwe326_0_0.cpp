#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Varsayılan anahtar uzunluğu 2048 bit olarak ayarlanmıştır
    const int key_length = 2048;
    
    // OpenSSL komutunu oluştur
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Komutu çalıştırmak için pipe aç
    std::array<char, 128> buffer;
    std::string result;
    
    // Komutu çalıştır ve çıktısını oku
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Pipe açılamadı, NULL yerine boş string döndür
        return std::string();
    }
    
    // Çıktıyı oku
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Komut başarısız olduysa (boş çıktı) veya hata oluştuysa boş string döndür
    if (result.empty()) {
        return std::string();
    }
    
    return result;
}