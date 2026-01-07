#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 데이터를 파싱하기 위한 간단한 파서
    std::vector<std::string> tags;
    std::string current_tag;
    std::string current_value;
    bool in_tag = false;
    bool in_value = false;
    
    std::map<std::string, std::string> student_data;
    bool in_student = false;
    bool found_username = false;
    bool found_password = false;
    
    for (size_t i = 0; i < xml_data.length(); i++) {
        char c = xml_data[i];
        
        if (c == '<') {
            // 태그 시작
            if (i + 1 < xml_data.length() && xml_data[i + 1] == '/') {
                // 닫는 태그
                in_tag = true;
                current_tag.clear();
                i++; // '/' 건너뛰기
            } else {
                // 여는 태그
                in_tag = true;
                current_tag.clear();
            }
        } else if (c == '>') {
            // 태그 종료
            in_tag = false;
            
            if (!current_tag.empty() && current_tag[0] != '/') {
                // 여는 태그
                tags.push_back(current_tag);
                
                if (current_tag == "student") {
                    in_student = true;
                    student_data.clear();
                    found_username = false;
                    found_password = false;
                }
                
                // 값 읽기 시작
                in_value = true;
                current_value.clear();
            } else if (!current_tag.empty() && current_tag[0] == '/') {
                // 닫는 태그
                std::string tag_name = current_tag.substr(1);
                
                if (!tags.empty() && tags.back() == tag_name) {
                    tags.pop_back();
                    
                    if (tag_name == "student") {
                        // 학생 정보 완성, 검사
                        if (found_username && found_password) {
                            // 찾은 학생 정보 반환
                            result = student_data;
                            break;
                        }
                        in_student = false;
                    } else if (in_student && !current_value.empty()) {
                        // 태그 값 저장
                        std::string value = current_value;
                        
                        // 공백 제거
                        size_t start = value.find_first_not_of(" \t\n\r");
                        size_t end = value.find_last_not_of(" \t\n\r");
                        if (start != std::string::npos && end != std::string::npos) {
                            value = value.substr(start, end - start + 1);
                        }
                        
                        student_data[tag_name] = value;
                        
                        // 사용자 이름과 비밀번호 확인
                        if (tag_name == "username" && value == username) {
                            found_username = true;
                        } else if (tag_name == "password" && value == password) {
                            found_password = true;
                        }
                    }
                }
                in_value = false;
            }
        } else if (in_tag) {
            // 태그 이름 읽기
            current_tag += c;
        } else if (in_value) {
            // 태그 값 읽기
            current_value += c;
        }
    }
    
    return result;
}