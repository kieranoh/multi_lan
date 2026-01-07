#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// pugixml 헤더 (외부 라이브러리)
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
    
    // 일치하는 학생이 있는 경우
    if (!students.empty()) {
        pugi::xpath_node student_node = students[0];
        pugi::xml_node student = student_node.node();
        
        // 이름 추출
        pugi::xml_node name_node = student.child("name");
        if (name_node) {
            result["name"] = name_node.text().get();
        }
        
        // 나이 추출
        pugi::xml_node age_node = student.child("age");
        if (age_node) {
            result["age"] = age_node.text().get();
        }
        
        // 시민권 추출
        pugi::xml_node citizenship_node = student.child("citizenship");
        if (citizenship_node) {
            result["citizenship"] = citizenship_node.text().get();
        }
    }
    
    return result;
}