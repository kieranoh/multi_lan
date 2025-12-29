#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <pwd.h>
#endif

/**
 * एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजें।
 * फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।
 *
 * @param directory गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
 * @param filename गुप्त फ़ाइल का फ़ाइल नाम।
 * @param content गुप्त फ़ाइल की सामग्री।
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // निर्देशिका और फ़ाइल पथ बनाएं
    std::filesystem::path dir_path(directory);
    std::filesystem::path file_path = dir_path / filename;
    
    // निर्देशिका बनाएं यदि मौजूद नहीं है
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }
    
    // फ़ाइल लिखें
    std::ofstream file(file_path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("फ़ाइल खोलने में विफल: " + file_path.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // फ़ाइल अनुमतियाँ सेट करें (केवल वर्तमान उपयोगकर्ता के लिए पढ़ने/लिखने की अनुमति)
    #ifdef _WIN32
        // Windows के लिए: फ़ाइल सुरक्षा विवरणक सेट करें
        std::wstring wpath = file_path.wstring();
        DWORD dwRes = SetNamedSecurityInfoW(
            const_cast<LPWSTR>(wpath.c_str()),
            SE_FILE_OBJECT,
            OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
            NULL, NULL, NULL, NULL
        );
        if (dwRes != ERROR_SUCCESS) {
            throw std::runtime_error("Windows पर फ़ाइल अनुमतियाँ सेट करने में विफल");
        }
    #else
        // Unix-like सिस्टम के लिए: chmod का उपयोग करें (0600 - केवल स्वामी पढ़/लिख सकता है)
        if (chmod(file_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
            throw std::runtime_error("Unix पर फ़ाइल अनुमतियाँ सेट करने में विफल");
        }
        
        // स्वामित्व सुनिश्चित करें (वैकल्पिक, लेकिन अनुशंसित)
        #ifndef _WIN32
            uid_t current_uid = geteuid();
            if (chown(file_path.c_str(), current_uid, -1) != 0) {
                // चेतावनी लॉग कर सकते हैं, लेकिन अपवाद नहीं फेंकते क्योंकि यह गंभीर नहीं है
            }
        #endif
    #endif
}