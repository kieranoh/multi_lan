#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 전달하기 위해 따옴표로 감쌈
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // popen을 사용하여 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 출력 읽기
    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 RAII를 통해 자동으로 호출되지만, 명시적으로 상태 확인
    // 이미 unique_ptr 소멸자에서 pclose가 호출되므로 추가 확인 불필요
    
    // 결과가 비어있거나 오류 발생 시 빈 문자열 반환
    // ls -l은 오류 발생 시 stderr로 출력하므로 2>/dev/null로 제거됨
    // 따라서 결과가 비어있으면 오류로 간주
    if (result.empty()) {
        return "";
    }
    
    return result;
}