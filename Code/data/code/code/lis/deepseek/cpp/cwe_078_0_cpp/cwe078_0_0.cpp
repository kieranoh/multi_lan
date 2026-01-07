#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

/* 사용자가 제공한 디렉토리 경로에서 `ls -l` 명령을 실행할 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자가 제공한 디렉토리 경로입니다.

@return `ls -l` 명령의 출력 또는 오류가 발생할 경우 빈 문자열입니다. */
std::string get_ls_result(const std::string &dir_path) {
    // 명령어 구성: 디렉토리 경로를 안전하게 인용하여 명령어 삽입 공격 방지
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 파이프를 열어 명령어 실행
    std::array<char, 128> buffer;
    std::string result;
    
    // popen을 사용하여 명령어 실행 및 출력 읽기
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen 실패 시 빈 문자열 반환
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // pclose는 unique_ptr 소멸 시 자동으로 호출됨
    
    return result;
}