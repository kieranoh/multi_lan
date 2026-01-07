#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>

// Bir shell komutunu çalıştıran ve çıktısını yakalayan fonksiyon
std::string execute_command(const std::string& command);

/* Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün. */
std::string create_dsa_key() {
    const int key_length = 1024; // DSA anahtar uzunluğu
    
    // 1. DSA parametreleri için geçici dosya oluştur
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        throw std::runtime_error("Geçici parametre dosyası oluşturulamadı");
    }
    close(param_fd); // Dosya tanımlayıcısını kapat, sadece dosya adına ihtiyacımız var
    
    // 2. Özel anahtar için geçici dosya oluştur
    char key_filename[] = "/tmp/dsa_key_XXXXXX";
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename); // Temizlik
        throw std::runtime_error("Geçici anahtar dosyası oluşturulamadı");
    }
    close(key_fd); // Dosya tanımlayıcısını kapat
    
    try {
        // 3. DSA parametrelerini oluştur
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length) + " 2>&1";
        std::string param_output = execute_command(param_command);
        
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("DSA parametreleri oluşturulamadı: " + param_output);
        }
        
        // 4. DSA özel anahtarını oluştur
        std::string key_command = "openssl gendsa -out " + std::string(key_filename) + 
                                 " " + std::string(param_filename) + " 2>&1";
        std::string key_output = execute_command(key_command);
        
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("DSA anahtarı oluşturulamadı: " + key_output);
        }
        
        // 5. PEM formatında anahtarı oku
        std::string read_command = "cat " + std::string(key_filename);
        std::string pem_key = execute_command(read_command);
        
        // 6. Geçici dosyaları temizle
        unlink(param_filename);
        unlink(key_filename);
        
        return pem_key;
        
    } catch (...) {
        // Hata durumunda geçici dosyaları temizle
        unlink(param_filename);
        unlink(key_filename);
        throw;
    }
}