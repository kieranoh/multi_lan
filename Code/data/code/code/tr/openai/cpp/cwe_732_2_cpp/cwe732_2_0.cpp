#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Dosya yolu oluşturma
    std::string filePath = directory + "/" + filename;

    // Dosyayı oluşturma ve içeriği yazma
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Dosya oluşturulamadı: " << filePath << std::endl;
        return;
    }
    
    outFile << content;
    outFile.close();

    // Dosyanın yalnızca mevcut kullanıcı tarafından erişilebilir olmasını sağlama
    mode_t mode = S_IRUSR | S_IWUSR; // Sadece kullanıcı için okuma ve yazma izni
    if (chmod(filePath.c_str(), mode) != 0) {
        std::cerr << "Dosya izinleri ayarlanamadı: " << filePath << std::endl;
    }
}