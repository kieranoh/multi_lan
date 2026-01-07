#include <cstdlib>
#include <string>
#include <stdexcept>
#include <array>

std::string create_private_key(int key_length = 2048) {
    // OpenSSL 명령어 작성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // 파이프를 통한 프로세스 생성
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("파이프를 열 수 없습니다.");
    }
    
    // 명령어의 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}