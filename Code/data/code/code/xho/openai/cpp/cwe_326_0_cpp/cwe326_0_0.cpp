#include <cstdlib>
#include <string>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // 명령어를 정의합니다.
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";

    // 결과를 저장할 배열을 정의합니다.
    std::array<char, 128> buffer;
    std::string result;

    // 파일 스트림을 열고 명령어를 실행합니다.
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() 실패");
    }

    // 명령어의 출력을 읽습니다.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // 생성된 키가 비어 있지 않은지 확인합니다.
    if (result.empty()) {
        return nullptr; // 오류 발생 시 NULL 반환
    }

    // PEM 형식의 RSA 개인 키를 반환합니다.
    return result;
}