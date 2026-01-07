#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

// Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin.
// Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.
//
// @param directory Gizli dosyanın kaydedileceği dizin.
// @param filename Gizli dosyanın dosya adı.
// @param content Gizli dosyanın içeriği.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    try {
        // Dizin yolunu oluştur
        std::filesystem::path dir_path(directory);
        
        // Dizinin var olup olmadığını kontrol et, yoksa oluştur
        if (!std::filesystem::exists(dir_path)) {
            std::filesystem::create_directories(dir_path);
            
            // Dizini yalnızca mevcut kullanıcı için erişilebilir yap
            std::filesystem::permissions(dir_path,
                std::filesystem::perms::owner_all |
                std::filesystem::perms::group_exec |  // Grup yürütme izni
                std::filesystem::perms::others_exec,  // Diğerleri yürütme izni
                std::filesystem::perm_options::replace);
        }
        
        // Tam dosya yolunu oluştur
        std::filesystem::path file_path = dir_path / filename;
        
        // Dosyayı yazma modunda aç
        std::ofstream out_file(file_path, std::ios::binary);
        
        if (!out_file.is_open()) {
            throw std::runtime_error("Dosya oluşturulamadı veya yazma için açılamadı.");
        }
        
        // İçeriği dosyaya yaz
        out_file.write(content.c_str(), content.size());
        
        if (!out_file.good()) {
            throw std::runtime_error("Dosyaya yazma sırasında hata oluştu.");
        }
        
        out_file.close();
        
        // Dosya izinlerini ayarla: yalnızca sahibi okuyabilir ve yazabilir (600)
        std::filesystem::permissions(file_path,
            std::filesystem::perms::owner_read | std::filesystem::perms::owner_write,
            std::filesystem::perm_options::replace);
        
        // Dosyanın sahibini mevcut kullanıcı yap (isteğe bağlı, ancak güvenlik için iyi)
        // Not: Bu işlem root yetkileri gerektirebilir
        struct passwd *pw = getpwuid(getuid());
        if (pw != nullptr) {
            // chown çağrısı root yetkisi gerektirir, bu yüzden sadece deneyebiliriz
            // Gerçek uygulamada bu kısım kaldırılabilir veya koşullu yapılabilir
            chown(file_path.c_str(), getuid(), getgid());
        }
        
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error(std::string("Dosya sistemi hatası: ") + e.what());
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Gizli dosya kaydedilemedi: ") + e.what());
    }
}