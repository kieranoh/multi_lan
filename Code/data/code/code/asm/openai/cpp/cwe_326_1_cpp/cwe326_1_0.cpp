#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

// 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생
    }
    close(fd); // 파일 디스크립터는 더 이상 필요하지 않음

    // DSA 파라미터 생성 명령어
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) == nullptr) {
        return nullptr; // 오류 발생
    }

    // DSA 개인 키 생성 명령어
    std::string key_command = "openssl gendsa -out " + std::string(param_filename) + ".key " + param_filename;
    if (execute_command(key_command) == nullptr) {
        return nullptr; // 오류 발생
    }

    // 키 파일을 읽어와서 PEM 형식의 DSA 개인 키를 반환
    std::string key_filename = std::string(param_filename) + ".key";
    std::string private_key = execute_command("cat " + key_filename);

    // 임시 파일 삭제
    std::remove(param_filename);
    std::remove(key_filename.c_str());

    return private_key;
}