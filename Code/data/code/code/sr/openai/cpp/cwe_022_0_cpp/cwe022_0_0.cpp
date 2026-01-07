#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string file_path = dir_path + "/" + filename;
    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        return ""; // Vraćamo prazan string ako ne možemo otvoriti datoteku
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf(); // Čitamo sadržaj datoteke u buffer
    return buffer.str(); // Vraćamo sadržaj datoteke
}