#include <string>
#include <array>
#include <stdexcept>
#include <memory>
#include <iostream>

std::string get_ls_result(const std::string &dir_path) {
    // 커맨드 조합
    std::string command = "ls -l " + dir_path;

    // 파이프를 통해 커맨드를 실행하고 출력을 캡처
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // 파이프가 유효한지 확인
    if (!pipe) {
        return "";
    }
    
    // 파이프에서 출력을 읽어들임
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}