#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // कमांड तैयार करें, dir_path को उद्धरणों में लपेटें ताकि रिक्त स्थान और विशेष वर्णों को संभाला जा सके
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // पाइप खोलें और कमांड निष्पादित करें
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // पाइप खोलने में विफल
        return "";
    }
    
    // आउटपुट पढ़ें
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // यदि परिणाम खाली है या त्रुटि हुई है, तो खाली स्ट्रिंग लौटाएं
    if (result.empty()) {
        return "";
    }
    
    return result;
}