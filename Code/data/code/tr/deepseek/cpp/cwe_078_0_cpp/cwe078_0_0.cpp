#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Komutu oluştur: ls -l ile dizin yolunu birleştir
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Pipe aç ve komutu çalıştır
    std::array<char, 128> buffer;
    std::string result;
    
    // popen kullanarak komutu çalıştır ve çıktıyı oku
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Pipe açılamadı, boş dize döndür
        return "";
    }
    
    // Çıktıyı oku
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Komut başarısız olduysa (boş çıktı veya hata) boş dize döndür
    // ls -l en az bir satır (toplam satırı) döndürür, bu yüzden boşsa hata vardır
    if (result.empty()) {
        return "";
    }
    
    return result;
}