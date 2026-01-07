#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>

// 함수 선언: 셸 명령을 실행하고 그 출력을 캡처합니다.
std::string execute_command(const std::string& command);

/**
 * @brief 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
 * 
 * DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 실행합니다:
 * 1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
 * 2. `openssl gendsa <매개변수를 저장할 임시 파일>`
 * 
 * @return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 빈 문자열.
 */
std::string create_dsa_key() {
    // DSA 매개변수 파일의 고유한 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("mkstemp failed");
        return "";
    }
    close(fd); // 파일 디스크립터를 닫습니다.
    
    // 키 길이 설정
    int key_length = 2048; // 키 길이 (예: 2048 비트)

    // DSA 매개변수 생성 명령
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    std::string result = execute_command(param_command);
    
    if (result.empty()) {
        return ""; // 오류가 발생한 경우 빈 문자열 반환
    }

    // DSA 개인 키 생성 명령
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    // 임시 파일 삭제
    std::remove(param_filename);

    // 생성된 DSA 개인 키 반환
    return private_key;
}

// 예시로 사용할 execute_command 구현 (실제로는 나중에 구현되어야 함)
std::string execute_command(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}