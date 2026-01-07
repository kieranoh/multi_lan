#include <iostream>
#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    tinyxml2::XMLDocument doc;
    std::map<std::string, std::string> student_info;

    // XML 데이터 로드
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // 파싱 실패 시 빈 맵 반환
    }

    // 학생 노드 검색
    tinyxml2::XMLElement* student = doc.FirstChildElement("students")->FirstChildElement("student");
    while (student != nullptr) {
        const char* user_elem = student->FirstChildElement("username")->GetText();
        const char* pass_elem = student->FirstChildElement("password")->GetText();

        // 사용자 이름과 비밀번호가 일치하는지 확인
        if (user_elem && pass_elem && username == user_elem && password == pass_elem) {
            const char* name_elem = student->FirstChildElement("name")->GetText();
            const char* citizenship_elem = student->FirstChildElement("citizenship")->GetText();
            const char* age_elem = student->FirstChildElement("age")->GetText();

            if (name_elem) student_info["name"] = name_elem;
            if (citizenship_elem) student_info["citizenship"] = citizenship_elem;
            if (age_elem) student_info["age"] = age_elem;

            return student_info; // 찾은 학생 정보 반환
        }
        student = student->NextSiblingElement("student");
    }

    return student_info; // 학생을 찾지 못한 경우 빈 맵 반환
}