#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// pugixml 헤더 - XML 파싱 라이브러리
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
    
    // XPath 쿼리 구성 - 주어진 username과 password에 해당하는 student 노드 찾기
    std::stringstream xpath_query;
    xpath_query << "/students/student[username='" << username << "' and password='" << password << "']";
    
    // XPath 쿼리 실행
    pugi::xpath_node_set students = doc.select_nodes(xpath_query.str().c_str());
    
    // 결과가 없으면 빈 맵 반환
    if (students.empty()) {
        return result;
    }
    
    // 첫 번째 매칭된 student 노드 가져오기
    pugi::xpath_node matched_student = students[0];
    pugi::xml_node student_node = matched_student.node();
    
    // 필요한 정보 추출
    pugi::xml_node name_node = student_node.child("name");
    pugi::xml_node citizenship_node = student_node.child("citizenship");
    pugi::xml_node age_node = student_node.child("age");
    
    // 정보가 모두 존재하는지 확인하고 맵에 추가
    if (name_node && citizenship_node && age_node) {
        result["name"] = name_node.text().as_string();
        result["citizenship"] = citizenship_node.text().as_string();
        result["age"] = age_node.text().as_string();
    }
    
    return result;
}