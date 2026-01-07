#include <string>
#include <memory>
#include <cstdio>
#include <stdexcept>

std::string create_private_key() {
    // 키 길이를 2048비트로 설정
    const int key_length = 2048;
    
    // 명령어 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                          std::to_string(key_length) + " 2>/dev/null";
    
    // 파일 포인터를 위한 스마트 포인터 (자동 정리)
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 열기 실패
        return "";
    }
    
    std::string result;
    char buffer[256];
    
    // 명령어 출력 읽기
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    // 명령어 실행 상태 확인
    int status = pclose(pipe.release());
    if (status != 0) {
        // 명령어 실행 실패
        return "";
    }
    
    // 결과가 비어있는지 확인
    if (result.empty()) {
        return "";
    }
    
    return result;
}