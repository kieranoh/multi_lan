#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: ls -l 뒤에 디렉토리 경로 추가
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // popen을 사용하여 명령 실행
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령 실행 실패(디렉토리 없음, 권한 오류 등) 시 빈 문자열 반환
    // ls -l은 오류가 발생하면 stderr로 출력하므로 2>/dev/null로 제거됨
    // 결과가 비어있거나 오류 메시지가 포함되어 있지 않은지 확인
    if (result.empty()) {
        return "";
    }
    
    return result;
}