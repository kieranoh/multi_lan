#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // XML 데이터 로드
    if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
        return student_info; // 파싱 에러 발생 시 빈 맵 반환
    }

    // 학생 노드 검색
    tinyxml2::XMLElement* students_element = doc.FirstChildElement("students");
    if (students_element) {
        for (tinyxml2::XMLElement* student_element = students_element->FirstChildElement("student"); student_element != nullptr; student_element = student_element->NextSiblingElement("student")) {
            const char* user = student_element->FirstChildElement("username")->GetText();
            const char* pass = student_element->FirstChildElement("password")->GetText();
            
            // 사용자 이름과 비밀번호 확인
            if (user && pass && username == user && password == pass) {
                const char* name = student_element->FirstChildElement("name")->GetText();
                const char* citizenship = student_element->FirstChildElement("citizenship")->GetText();
                const char* age = student_element->FirstChildElement("age")->GetText();

                // 학생 정보를 맵에 추가
                if (name) student_info["name"] = name;
                if (citizenship) student_info["citizenship"] = citizenship;
                if (age) student_info["age"] = age;
                break; // 정보가 발견되면 루프 종료
            }
        }
    }

    return student_info; // 찾은 정보 또는 빈 맵 반환
}