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
    // إنشاء المسار الكامل للملف
    std::filesystem::path dirPath(directory);
    std::filesystem::path filePath = dirPath / filename;
    
    // التأكد من وجود الدليل
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    
    // حفظ المحتوى في الملف
    std::ofstream file(filePath.string(), std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("فشل في فتح الملف للكتابة: " + filePath.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // تعيين أذونات الملف لتكون للمستخدم الحالي فقط
    #ifdef _WIN32
        // Windows implementation
        std::wstring wpath = filePath.wstring();
        DWORD dwRes = SetNamedSecurityInfoW(
            const_cast<LPWSTR>(wpath.c_str()),
            SE_FILE_OBJECT,
            OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
            NULL, // المالك الحالي
            NULL, // المجموعة الأساسية الحالية
            NULL, // DACL جديد (NULL يعني لا وصول)
            NULL  // SACL
        );
        
        if (dwRes != ERROR_SUCCESS) {
            // محاولة بديلة: تعيين أذونات تقييدية
            HANDLE hFile = CreateFileW(
                wpath.c_str(),
                WRITE_OWNER | WRITE_DAC,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
            
            if (hFile != INVALID_HANDLE_VALUE) {
                // تعيين DACL فارغ (لا وصول لأي أحد)
                DWORD dwErr = SetSecurityInfo(
                    hFile,
                    SE_FILE_OBJECT,
                    DACL_SECURITY_INFORMATION,
                    NULL, NULL, NULL, NULL
                );
                CloseHandle(hFile);
                
                // الآن منح الوصول للمستخدم الحالي فقط
                hFile = CreateFileW(
                    wpath.c_str(),
                    WRITE_DAC,
                    0,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL
                );
                
                if (hFile != INVALID_HANDLE_VALUE) {
                    EXPLICIT_ACCESS_W ea;
                    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS_W));
                    
                    // الحصول على SID للمستخدم الحالي
                    HANDLE hToken;
                    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
                        DWORD dwSize = 0;
                        GetTokenInformation(hToken, TokenUser, NULL, 0, &dwSize);
                        if (dwSize > 0) {
                            PTOKEN_USER pTokenUser = (PTOKEN_USER)LocalAlloc(LPTR, dwSize);
                            if (pTokenUser && GetTokenInformation(hToken, TokenUser, pTokenUser, dwSize, &dwSize)) {
                                ea.grfAccessPermissions = GENERIC_ALL;
                                ea.grfAccessMode = SET_ACCESS;
                                ea.grfInheritance = NO_INHERITANCE;
                                ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
                                ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
                                ea.Trustee.ptstrName = (LPWSTR)pTokenUser->User.Sid;
                                
                                PACL pNewDacl = NULL;
                                if (SetEntriesInAclW(1, &ea, NULL, &pNewDacl) == ERROR_SUCCESS) {
                                    SetSecurityInfo(
                                        hFile,
                                        SE_FILE_OBJECT,
                                        DACL_SECURITY_INFORMATION,
                                        NULL, NULL, pNewDacl, NULL
                                    );
                                    LocalFree(pNewDacl);
                                }
                            }
                            if (pTokenUser) LocalFree(pTokenUser);
                        }
                        CloseHandle(hToken);
                    }
                    CloseHandle(hFile);
                }
            }
        }
    #else
        // Unix/Linux implementation
        // تعيين أذونات الملف إلى 600 (القراءة والكتابة للمالك فقط)
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
        
        // التأكد من أن الملف مملوك للمستخدم الحالي
        struct stat fileStat;
        if (stat(filePath.c_str(), &fileStat) == 0) {
            uid_t currentUid = getuid();
            if (fileStat.st_uid != currentUid) {
                // محاولة تغيير ملكية الملف للمستخدم الحالي
                if (chown(filePath.c_str(), currentUid, getgid()) != 0) {
                    // إذا فشل chown، قد نحتاج إلى صلاحيات root
                    // في هذه الحالة، نكتفي بالأذونات 600
                }
            }
        }
    #endif
}