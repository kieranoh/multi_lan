#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // 빈 경로인 경우 빈 문자열 반환
    if (dir_path.empty()) {
        return "";
    }
    
    // 명령어 구성: ls -l 경로
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 파일 포인터
    std::array<char, 128> buffer;
    std::string result;
    
    // popen으로 명령 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령 실행 결과 확인
    int status = pclose(pipe.release());
    if (status != 0) {
        // 명령 실패 시 빈 문자열 반환
        return "";
    }
    
    // 결과 반환 (공백만 있는 경우도 빈 문자열로 처리)
    if (result.empty() || result.find_first_not_of(" \t\n\r") == std::string::npos) {
        return "";
    }
    
    return result;
}