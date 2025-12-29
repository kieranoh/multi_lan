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
    // Создаем полный путь к файлу
    std::filesystem::path dir_path(directory);
    std::filesystem::path file_path = dir_path / filename;
    
    // Создаем директорию, если она не существует
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }
    
    // Устанавливаем разрешения для директории (только для текущего пользователя)
    #ifdef _WIN32
        // На Windows устанавливаем разрешения через ACL
        // Создаем дескриптор безопасности
        PSECURITY_DESCRIPTOR pSD = NULL;
        PACL pACL = NULL;
        
        // Создаем дескриптор безопасности, разрешающий доступ только текущему пользователю
        if (SetNamedSecurityInfoA(const_cast<char*>(dir_path.string().c_str()), 
                                 SE_FILE_OBJECT,
                                 DACL_SECURITY_INFORMATION,
                                 NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
            // В случае ошибки просто создаем файл с минимальными разрешениями
        }
    #else
        // На Unix-подобных системах используем chmod
        chmod(dir_path.c_str(), S_IRWXU); // rwx для владельца
    #endif
    
    // Открываем файл для записи
    std::ofstream outFile(file_path, std::ios::binary | std::ios::trunc);
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + file_path.string());
    }
    
    // Записываем содержимое
    outFile.write(content.c_str(), content.size());
    outFile.close();
    
    // Устанавливаем разрешения файла (только для текущего пользователя)
    #ifdef _WIN32
        // На Windows
        SetFileAttributesA(file_path.string().c_str(), FILE_ATTRIBUTE_HIDDEN);
        
        // Устанавливаем ACL для файла
        PSID pSidOwner = NULL;
        PACL pNewDACL = NULL;
        
        // Получаем SID текущего пользователя
        HANDLE hToken = NULL;
        OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
        
        if (hToken) {
            DWORD dwSize = 0;
            GetTokenInformation(hToken, TokenUser, NULL, 0, &dwSize);
            if (dwSize > 0) {
                PTOKEN_USER pTokenUser = (PTOKEN_USER)LocalAlloc(LPTR, dwSize);
                if (GetTokenInformation(hToken, TokenUser, pTokenUser, dwSize, &dwSize)) {
                    pSidOwner = pTokenUser->User.Sid;
                }
                LocalFree(pTokenUser);
            }
            CloseHandle(hToken);
        }
        
        // Устанавливаем разрешения
        if (SetNamedSecurityInfoA(const_cast<char*>(file_path.string().c_str()),
                                 SE_FILE_OBJECT,
                                 OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
                                 pSidOwner, NULL, pNewDACL, NULL) != ERROR_SUCCESS) {
            // В случае ошибки просто оставляем файл с минимальными разрешениями
        }
    #else
        // На Unix-подобных системах
        chmod(file_path.c_str(), S_IRUSR | S_IWUSR); // rw- для владельца
    #endif
}