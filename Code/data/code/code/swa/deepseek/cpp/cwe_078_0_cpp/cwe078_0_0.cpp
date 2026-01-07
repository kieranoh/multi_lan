#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: ls -l과 경로를 결합
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // popen을 사용하여 명령어 실행 및 출력 읽기
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 실행 상태 확인
    int status = pclose(pipe.release());
    if (status != 0) {
        // 명령어 실패 시 빈 문자열 반환
        return "";
    }
    
    return result;
}