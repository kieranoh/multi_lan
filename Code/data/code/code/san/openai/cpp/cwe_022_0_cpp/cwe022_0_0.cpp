#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

/**
 * 지정된 디렉토리 경로와 파일 이름을 받아, 디렉토리에서 파일을 읽고 그 내용을 반환합니다. 
 * 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param filename 사용자가 요청한 읽을 파일의 이름.
 * @param dir_path 파일이 위치한 디렉토리의 경로.
 *
 * @return 파일이 존재하고 접근 가능하면 파일의 내용, 그렇지 않으면 빈 문자열.
 */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // 파일의 전체 경로 생성
    std::ifstream file(full_path); // 파일 열기

    if (!file.is_open()) { // 파일 열기 실패 시
        return ""; // 빈 문자열 반환
    }

    std::string content;
    std::string line;

    while (std::getline(file, line)) { // 파일에서 한 줄씩 읽기
        content += line + "\n"; // 내용 추가
    }

    file.close(); // 파일 닫기
    return content; // 파일 내용 반환
}