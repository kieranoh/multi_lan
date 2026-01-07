#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Verwenden von std::filesystem für pfadbezogene Operationen
    namespace fs = std::filesystem;
    
    // Pfad zur Datei konstruieren
    fs::path file_path = fs::path(dir_path) / filename;
    
    // Prüfen, ob die Datei existiert und eine reguläre Datei ist
    std::error_code ec;
    if (!fs::exists(file_path, ec) || ec || !fs::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Versuchen, die Datei zu öffnen und zu lesen
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // Dateigröße ermitteln
    std::streamsize size = file.tellg();
    if (size == -1) {
        return "";
    }
    
    // Zurück zum Anfang der Datei gehen
    file.seekg(0, std::ios::beg);
    
    // String mit entsprechender Größe vorbereiten
    std::string content;
    content.resize(static_cast<size_t>(size));
    
    // Dateiinhalt lesen
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}