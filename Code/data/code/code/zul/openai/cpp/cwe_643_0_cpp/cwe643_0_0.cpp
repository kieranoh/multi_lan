#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    // XML 문서 객체 생성
    tinyxml2::XMLDocument doc;
    
    // XML 데이터 로드
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return {}; // XML 파싱 실패 시 빈 맵 반환
    }
    
    // 학생 노드 검색
    tinyxml2::XMLElement* root = doc.FirstChildElement("students");
    if (!root) {
        return {}; // 학생 루트 노드가 없으면 빈 맵 반환
    }

    // 모든 학생 노드를 반복하며 사용자 이름과 비밀번호를 확인
    for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
        const char* user = student->FirstChildElement("username")->GetText();
        const char* pass = student->FirstChildElement("password")->GetText();
        
        // 사용자 이름과 비밀번호가 일치하는 경우
        if (user && pass && username == user && password == pass) {
            // 학생 정보 수집
            std::map<std::string, std::string> student_info;
            student_info["name"] = student->FirstChildElement("name")->GetText() ? student->FirstChildElement("name")->GetText() : "";
            student_info["citizenship"] = student->FirstChildElement("citizenship")->GetText() ? student->FirstChildElement("citizenship")->GetText() : "";
            student_info["age"] = student->FirstChildElement("age")->GetText() ? student->FirstChildElement("age")->GetText() : "";
            return student_info; // 학생 정보를 반환
        }
    }
    
    return {}; // 일치하는 학생을 찾지 못한 경우 빈 맵 반환
}