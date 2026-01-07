#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // ls -l 명령어 구성
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 명령어 실행을 위한 파이프 열기
    std::array<char, 128> buffer;
    std::string result;
    
    // popen을 사용하여 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 실행 상태 확인
    int status = pclose(pipe.release());
    
    // 명령어가 실패했거나 출력이 없으면 빈 문자열 반환
    if (status != 0 || result.empty()) {
        return "";
    }
    
    return result;
}