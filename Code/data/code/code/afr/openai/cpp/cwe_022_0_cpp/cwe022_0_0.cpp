#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // 디렉토리와 파일 이름을 결합하여 전체 경로 생성
    std::ifstream file(full_path); // 파일 스트림 생성

    if (!file.is_open()) { // 파일 열기 실패 시
        return ""; // 빈 문자열 반환
    }

    std::string content; // 파일 내용을 저장할 문자열
    std::string line;

    while (std::getline(file, line)) { // 파일에서 행 단위로 읽기
        content += line + "\n"; // 읽은 행을 내용에 추가
    }

    file.close(); // 파일 닫기
    return content; // 파일 내용 반환
}