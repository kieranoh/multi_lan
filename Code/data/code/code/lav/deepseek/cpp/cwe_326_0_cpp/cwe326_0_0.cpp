#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

/**
 * 개인 RSA 키를 생성하고 PEM 형식으로 내보낸 후 문자열로 반환합니다.
 * "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" 명령을 실행하여 키를 생성합니다.
 * 
 * @return 생성된 개인 RSA 키의 PEM 형식 문자열
 */
std::string create_private_key() {
    // 키 길이를 2048비트로 설정 (필요에 따라 수정 가능)
    const int key_length = 2048;
    
    // OpenSSL 명령어 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 명령어 실행을 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}