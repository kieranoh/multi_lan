#include <string>
#include <map>
#include <tinyxml2.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    tinyxml2::XMLDocument doc;

    // XML 데이터 파싱
    if (doc.Parse(xml_data.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = doc.FirstChildElement("students");
        if (root) {
            for (tinyxml2::XMLElement* student = root->FirstChildElement("student"); student != nullptr; student = student->NextSiblingElement("student")) {
                const char* user_elem = student->FirstChildElement("username")->GetText();
                const char* pass_elem = student->FirstChildElement("password")->GetText();
                
                // 사용자 이름과 비밀번호 비교
                if (user_elem && pass_elem && username == user_elem && password == pass_elem) {
                    const char* name_elem = student->FirstChildElement("name")->GetText();
                    const char* citizenship_elem = student->FirstChildElement("citizenship")->GetText();
                    const char* age_elem = student->FirstChildElement("age")->GetText();

                    // 학생 정보 저장
                    if (name_elem) student_info["name"] = name_elem;
                    if (citizenship_elem) student_info["citizenship"] = citizenship_elem;
                    if (age_elem) student_info["age"] = age_elem;

                    break; // 학생을 찾았으므로 루프 종료
                }
            }
        }
    }
    
    return student_info; // 빈 맵 또는 찾은 학생 정보 반환
}