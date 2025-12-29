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

namespace fs = std::filesystem;

/**
 * Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud.
 * Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.
 *
 * @param directory De map om het geheime bestand op te slaan.
 * @param filename De bestandsnaam van het geheime bestand.
 * @param content De inhoud van het geheime bestand.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Controleer of de directory bestaat, zo niet, maak deze aan
    fs::path dir_path(directory);
    if (!fs::exists(dir_path)) {
        if (!fs::create_directories(dir_path)) {
            throw std::runtime_error("Kan directory niet aanmaken: " + directory);
        }
    }

    // Controleer of het pad een directory is
    if (!fs::is_directory(dir_path)) {
        throw std::runtime_error("Opgegeven pad is geen directory: " + directory);
    }

    // Construeer het volledige pad naar het bestand
    fs::path file_path = dir_path / filename;

    // Schrijf de inhoud naar het bestand
    std::ofstream out_file(file_path, std::ios::out | std::ios::binary);
    if (!out_file.is_open()) {
        throw std::runtime_error("Kan bestand niet openen voor schrijven: " + file_path.string());
    }
    out_file.write(content.c_str(), content.size());
    out_file.close();

    // Stel bestandspermissies in zodat alleen de huidige gebruiker toegang heeft
    #ifdef _WIN32
        // Windows: gebruik SetNamedSecurityInfo om DACL in te stellen
        std::wstring wpath = file_path.wstring();
        PACL pOldDACL = nullptr;
        PSECURITY_DESCRIPTOR pSD = nullptr;
        
        if (GetNamedSecurityInfoW(wpath.c_str(), SE_FILE_OBJECT,
                                  DACL_SECURITY_INFORMATION,
                                  nullptr, nullptr, &pOldDACL, nullptr, &pSD) == ERROR_SUCCESS) {
            // Haal de huidige gebruiker SID op
            HANDLE hToken = nullptr;
            OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
            
            DWORD dwSize = 0;
            GetTokenInformation(hToken, TokenUser, nullptr, 0, &dwSize);
            PTOKEN_USER pTokenUser = (PTOKEN_USER)new BYTE[dwSize];
            GetTokenInformation(hToken, TokenUser, pTokenUser, dwSize, &dwSize);
            
            // Maak een nieuwe DACL die alleen de huidige gebruiker toestaat
            EXPLICIT_ACCESS_W ea;
            ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS_W));
            ea.grfAccessPermissions = GENERIC_ALL;
            ea.grfAccessMode = SET_ACCESS;
            ea.grfInheritance = NO_INHERITANCE;
            ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
            ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
            ea.Trustee.ptstrName = (LPWSTR)pTokenUser->User.Sid;
            
            PACL pNewDACL = nullptr;
            if (SetEntriesInAclW(1, &ea, pOldDACL, &pNewDACL) == ERROR_SUCCESS) {
                SetNamedSecurityInfoW((LPWSTR)wpath.c_str(), SE_FILE_OBJECT,
                                      DACL_SECURITY_INFORMATION,
                                      nullptr, nullptr, pNewDACL, nullptr);
                LocalFree(pNewDACL);
            }
            
            delete[] (BYTE*)pTokenUser;
            CloseHandle(hToken);
            LocalFree(pSD);
        }
    #else
        // Unix/Linux/macOS: stel bestandspermissies in op 0600 (alleen eigenaar kan lezen/schrijven)
        if (chmod(file_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
            throw std::runtime_error("Kan bestandspermissies niet instellen voor: " + file_path.string());
        }
    #endif
}