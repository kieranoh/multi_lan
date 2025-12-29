#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // पूर्ण फ़ाइल पथ बनाएं
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // फ़ाइल के अस्तित्व और पठन योग्यता की जाँच करें
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // फ़ाइल एक नियमित फ़ाइल है और पढ़ने योग्य है यह सुनिश्चित करें
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // फ़ाइल खोलें
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // फ़ाइल सामग्री पढ़ें
    std::string content;
    file.seekg(0, std::ios::end);
    content.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    
    content.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    
    // फ़ाइल पढ़ने में त्रुटि की जाँच करें
    if (file.bad()) {
        return "";
    }
    
    return content;
}