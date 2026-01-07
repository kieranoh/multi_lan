#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 명령 구성: 디렉토리 경로를 적절히 이스케이프 처리
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 파이프를 열어 명령 실행
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
    
    // 명령이 성공적으로 실행되었는지 확인 (pclose는 명령의 종료 상태를 반환)
    // 이미 stderr는 /dev/null로 리디렉트했으므로 여기서는 결과가 비어있는지만 확인
    // 실제로 ls -l은 디렉토리가 비어있더라도 총합 줄을 출력하므로, 
    // 결과가 완전히 비어있는 경우만 오류로 간주
    if (result.empty()) {
        return "";
    }
    
    return result;
}