#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>

// पहले से घोषित फ़ंक्शन
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // DSA पैरामीटर फ़ाइल के लिए अस्थायी फ़ाइल नाम बनाएं
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // अस्थायी फ़ाइल बनाने में विफल
    }
    close(fd); // फ़ाइल डिस्क्रिप्टर बंद करें, हम केवल फ़ाइल नाम का उपयोग करेंगे

    // DSA निजी कुंजी के लिए अस्थायी फ़ाइल नाम बनाएं
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        remove(param_filename); // पैरामीटर फ़ाइल साफ़ करें
        return ""; // अस्थायी फ़ाइल बनाने में विफल
    }
    close(fd);

    // DSA पैरामीटर उत्पन्न करें (2048-बिट कुंजी लंबाई का उपयोग करें)
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    std::string param_output = execute_command(param_cmd);
    
    if (param_output.find("error") != std::string::npos || 
        param_output.find("Error") != std::string::npos ||
        param_output.empty()) {
        remove(param_filename);
        remove(key_filename);
        return ""; // पैरामीटर जनरेशन विफल
    }

    // DSA निजी कुंजी उत्पन्न करें
    std::string key_cmd = "openssl gendsa -out " + std::string(key_filename) + " " + std::string(param_filename);
    std::string key_output = execute_command(key_cmd);
    
    if (key_output.find("error") != std::string::npos || 
        key_output.find("Error") != std::string::npos ||
        key_output.empty()) {
        remove(param_filename);
        remove(key_filename);
        return ""; // कुंजी जनरेशन विफल
    }

    // उत्पन्न कुंजी फ़ाइल पढ़ें
    FILE* key_file = fopen(key_filename, "rb");
    if (!key_file) {
        remove(param_filename);
        remove(key_filename);
        return ""; // कुंजी फ़ाइल खोलने में विफल
    }

    // फ़ाइल का आकार प्राप्त करें
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    // फ़ाइल सामग्री पढ़ें
    std::unique_ptr<char[]> buffer(new char[file_size + 1]);
    size_t bytes_read = fread(buffer.get(), 1, file_size, key_file);
    fclose(key_file);

    std::string key_pem;
    if (bytes_read == static_cast<size_t>(file_size)) {
        buffer[bytes_read] = '\0';
        key_pem = buffer.get();
    }

    // अस्थायी फ़ाइलें साफ़ करें
    remove(param_filename);
    remove(key_filename);

    // यह सुनिश्चित करें कि आउटपुट वास्तव में PEM प्रारूप में है
    if (key_pem.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos ||
        key_pem.find("-----END DSA PRIVATE KEY-----") == std::string::npos) {
        return ""; // अमान्य PEM प्रारूप
    }

    return key_pem;
}