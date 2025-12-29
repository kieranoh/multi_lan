#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

namespace fs = std::filesystem;

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Utwórz pełną ścieżkę do pliku
    fs::path dir_path(directory);
    fs::path file_path = dir_path / filename;
    
    // Upewnij się, że katalog istnieje
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
    
    // Zapisz treść do pliku
    std::ofstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku do zapisu: " + file_path.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    if (!file.good()) {
        throw std::runtime_error("Błąd podczas zapisywania pliku: " + file_path.string());
    }
    
    // Ustaw uprawnienia tylko dla właściciela (użytkownika)
    // 600 w systemie ósemkowym: właściciel może czytać i pisać, inni nie mają dostępu
    if (chmod(file_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Nie można ustawić uprawnień pliku: " + file_path.string());
    }
    
    // Dodatkowo upewnij się, że właścicielem pliku jest bieżący użytkownik
    // i że grupa oraz inni nie mają dostępu
    struct stat file_stat;
    if (stat(file_path.c_str(), &file_stat) == 0) {
        uid_t current_uid = geteuid();
        
        // Jeśli właścicielem nie jest bieżący użytkownik, zmień właściciela
        if (file_stat.st_uid != current_uid) {
            if (chown(file_path.c_str(), current_uid, -1) != 0) {
                throw std::runtime_error("Nie można zmienić właściciela pliku: " + file_path.string());
            }
        }
        
        // Upewnij się, że uprawnienia są prawidłowe (tylko właściciel ma dostęp)
        mode_t desired_permissions = S_IRUSR | S_IWUSR;
        if ((file_stat.st_mode & 0777) != desired_permissions) {
            if (chmod(file_path.c_str(), desired_permissions) != 0) {
                throw std::runtime_error("Nie można ustawić uprawnień pliku: " + file_path.string());
            }
        }
    }
    
    // Ustaw również uprawnienia dla katalogu, jeśli to konieczne
    // (tylko właściciel ma dostęp do katalogu)
    if (chmod(dir_path.c_str(), S_IRWXU) != 0) {
        // To jest opcjonalne, ponieważ katalog mógł już istnieć z innymi uprawnieniami
        // W praktyce lepiej nie zmieniać uprawnień istniejących katalogów bez potrzeby
    }
}