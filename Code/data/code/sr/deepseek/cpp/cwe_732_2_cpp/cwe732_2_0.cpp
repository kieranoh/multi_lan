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
    // Kreirajte punu putanju do fajla
    std::filesystem::path dir_path(directory);
    std::filesystem::path file_path = dir_path / filename;
    
    // Proverite da li direktorijum postoji, ako ne, kreirajte ga
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }
    
    // Otvorite fajl za pisanje
    std::ofstream out_file(file_path, std::ios::binary);
    if (!out_file.is_open()) {
        throw std::runtime_error("Nije moguće otvoriti fajl za pisanje: " + file_path.string());
    }
    
    // Zapišite sadržaj
    out_file.write(content.c_str(), content.size());
    out_file.close();
    
    // Postavite dozvole tako da samo trenutni korisnik može da pristupi
    #ifdef _WIN32
        // Windows implementacija
        std::wstring wpath = file_path.wstring();
        DWORD dwRes = SetNamedSecurityInfoW(
            const_cast<LPWSTR>(wpath.c_str()),
            SE_FILE_OBJECT,
            OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
            NULL, // Vlasnik - podrazumevano trenutni korisnik
            NULL, // Primarna grupa - podrazumevano
            NULL, // DACL - postavite na NULL da biste zabranili pristup svima
            NULL  // SACL
        );
        
        if (dwRes != ERROR_SUCCESS) {
            // Ako ne uspe, pokušajte sa osnovnim pristupom
            _wchmod(wpath.c_str(), _S_IREAD | _S_IWRITE);
        }
    #else
        // Unix/Linux implementacija
        // Postavite dozvole na 600 (samo vlasnik može da čita i piše)
        chmod(file_path.c_str(), S_IRUSR | S_IWUSR);
        
        // Obezbedite da je vlasnik trenutni korisnik
        struct stat fileStat;
        if (stat(file_path.c_str(), &fileStat) == 0) {
            uid_t current_uid = geteuid();
            if (fileStat.st_uid != current_uid) {
                chown(file_path.c_str(), current_uid, -1);
            }
        }
    #endif
}