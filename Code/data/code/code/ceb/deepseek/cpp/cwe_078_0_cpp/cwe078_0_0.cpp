#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: ls -l 뒤에 디렉토리 경로 추가
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 출력 캡처를 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // popen 실패 시 빈 문자열 반환
    if (!pipe) {
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 종료 상태 확인
    int status = pclose(pipe.release());
    
    // 명령어가 실패했거나 오류가 발생한 경우 빈 문자열 반환
    if (status != 0) {
        return "";
    }
    
    return result;
}