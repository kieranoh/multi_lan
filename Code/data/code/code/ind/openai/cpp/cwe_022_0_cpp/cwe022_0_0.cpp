#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        return ""; // 파일을 열 수 없거나 존재하지 않음
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str(); // 파일 내용 반환
}