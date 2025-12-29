#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <pwd.h>
#endif

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Erstelle das Verzeichnis, falls es nicht existiert
    std::filesystem::create_directories(directory);
    
    // Erstelle den vollständigen Dateipfad
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;
    
    // Öffne die Datei zum Schreiben
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Konnte Datei nicht öffnen: " + filePath.string());
    }
    
    // Schreibe den Inhalt in die Datei
    file.write(content.c_str(), content.size());
    file.close();
    
    // Setze Dateiberechtigungen so, dass nur der aktuelle Benutzer Zugriff hat
    #ifdef _WIN32
        // Windows-Implementierung
        std::wstring wpath = filePath.wstring();
        DWORD dwRes = SetNamedSecurityInfoW(
            const_cast<LPWSTR>(wpath.c_str()),
            SE_FILE_OBJECT,
            OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
            NULL,   // Owner (NULL = aktueller Benutzer)
            NULL,   // Group
            NULL,   // DACL (NULL = nur Besitzer)
            NULL    // SACL
        );
        
        if (dwRes != ERROR_SUCCESS) {
            // Fallback: Versuche, die Datei auf schreibgeschützt für den Besitzer zu setzen
            SetFileAttributesW(wpath.c_str(), FILE_ATTRIBUTE_READONLY);
        }
    #else
        // Unix/Linux/macOS Implementierung
        // Setze Berechtigungen auf 0600 (nur Besitzer kann lesen/schreiben)
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
        
        // Optional: Stelle sicher, dass der Besitzer der aktuelle Benutzer ist
        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) == 0) {
            uid_t currentUid = geteuid();
            if (fileStat.st_uid != currentUid) {
                chown(filePath.c_str(), currentUid, -1); // -1 behält die Gruppe bei
            }
        }
    #endif
}