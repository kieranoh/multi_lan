#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// PugiXML 라이브러리 헤더
#include "pugixml.hpp"

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 객체 생성
    pugi::xml_document doc;
    
    // XML 데이터 파싱
    pugi::xml_parse_result parse_result = doc.load_string(xml_data.c_str());
    
    // 파싱 실패 시 빈 맵 반환
    if (!parse_result) {
        return result;
    }
    
    // XPath 쿼리 구성
    std::stringstream xpath_query;
    xpath_query << "/students/student[username='" << username << "' and password='" << password << "']";
    
    // XPath 쿼리 실행
    pugi::xpath_node_set students = doc.select_nodes(xpath_query.str().c_str());
    
    // 일치하는 학생이 있는지 확인
    if (students.empty()) {
        return result;
    }
    
    // 첫 번째 일치하는 학생 노드 가져오기 (사용자명/비밀번호는 고유해야 함)
    pugi::xml_node student_node = students[0].node();
    
    // 학생 정보 추출
    std::string name = student_node.child("name").text().as_string();
    std::string citizenship = student_node.child("citizenship").text().as_string();
    std::string age = student_node.child("age").text().as_string();
    
    // 결과 맵에 저장
    result["name"] = name;
    result["citizenship"] = citizenship;
    result["age"] = age;
    
    return result;
}