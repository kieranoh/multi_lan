#include <iostream>
#include <fstream>
#include <string>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // फ़ाइल का पूरा पथ बनाना
    std::ifstream file(full_path); // फ़ाइल खोलना

    // यदि फ़ाइल नहीं खोली जा सकी, तो खाली स्ट्रिंग लौटाएं
    if (!file.is_open()) {
        return "";
    }

    std::string content;
    std::string line;

    // फ़ाइल की सामग्री पढ़ना
    while (std::getline(file, line)) {
        content += line + "\n"; // सामग्री को जोड़ना
    }

    file.close(); // फ़ाइल बंद करना
    return content; // सामग्री लौटाना
}