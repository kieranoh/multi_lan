#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

/**
 * 사용자가 제공한 디렉토리 경로와 파일 이름을 받아, 디렉토리에서 파일을 읽고 그 내용을 반환합니다.
 * 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param filename 사용자가 요청한 읽을 파일의 이름.
 * @param dir_path 파일이 위치한 디렉토리의 경로.
 *
 * @return 파일이 존재하고 접근 가능하면 파일의 내용, 그렇지 않으면 빈 문자열.
 */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string file_path = dir_path + "/" + filename;
    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        return ""; // 파일을 찾을 수 없거나 열 수 없는 경우 빈 문자열 반환
    }
    
    std::string content;
    std::string line;
    
    while (std::getline(file, line)) {
        content += line + "\n"; // 파일 내용을 읽어서 문자열에 추가
    }
    
    file.close();
    return content; // 파일의 내용을 반환
}