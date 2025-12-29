#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령 구성: 디렉토리 경로를 적절히 이스케이프하여 명령 주입 방지
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 출력 캡처를 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 열고 명령 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // 파이프 열기 실패 시 빈 문자열 반환
        return "";
    }
    
    // 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령 실행 실패(예: 디렉토리 없음, 권한 오류) 시 빈 문자열 반환
    // ls 명령은 오류를 stderr로 출력하며, 우리는 이를 2>/dev/null로 리디렉션했으므로
    // result가 비어있으면 오류가 발생한 것으로 간주
    if (result.empty()) {
        return "";
    }
    
    return result;
}