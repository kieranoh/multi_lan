#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// pugixml 헤더 - 실제 구현에서는 이 헤더를 포함해야 합니다
// #include "pugixml.hpp"

// pugixml을 사용하지 않고 간단한 XML 파싱을 위한 헬퍼 함수들
namespace xml_helper {
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }

    std::vector<std::string> extract_tags(const std::string& xml, const std::string& tag_name) {
        std::vector<std::string> results;
        std::string start_tag = "<" + tag_name + ">";
        std::string end_tag = "</" + tag_name + ">";
        
        size_t pos = 0;
        while ((pos = xml.find(start_tag, pos)) != std::string::npos) {
            size_t start = pos + start_tag.length();
            size_t end = xml.find(end_tag, start);
            if (end == std::string::npos) break;
            
            std::string content = xml.substr(start, end - start);
            results.push_back(trim(content));
            pos = end + end_tag.length();
        }
        
        return results;
    }

    std::string get_tag_content(const std::string& xml_fragment, const std::string& tag_name) {
        std::string start_tag = "<" + tag_name + ">";
        std::string end_tag = "</" + tag_name + ">";
        
        size_t start = xml_fragment.find(start_tag);
        if (start == std::string::npos) return "";
        
        start += start_tag.length();
        size_t end = xml_fragment.find(end_tag, start);
        if (end == std::string::npos) return "";
        
        return trim(xml_fragment.substr(start, end - start));
    }
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML에서 모든 student 태그 추출
    std::vector<std::string> students = xml_helper::extract_tags(xml_data, "student");
    
    for (const auto& student_xml : students) {
        // 각 student 태그에서 username과 password 추출
        std::string student_username = xml_helper::get_tag_content(student_xml, "username");
        std::string student_password = xml_helper::get_tag_content(student_xml, "password");
        
        // 사용자 이름과 비밀번호가 일치하는지 확인
        if (student_username == username && student_password == password) {
            // 일치하는 경우 모든 정보 추출
            std::string name = xml_helper::get_tag_content(student_xml, "name");
            std::string citizenship = xml_helper::get_tag_content(student_xml, "citizenship");
            std::string age = xml_helper::get_tag_content(student_xml, "age");
            
            // 결과 맵에 추가
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            // 일치하는 학생을 찾았으므로 반환
            return result;
        }
    }
    
    // 일치하는 학생을 찾지 못한 경우 빈 맵 반환
    return result;
}

// pugixml을 사용하는 실제 구현 (주석 처리됨)
/*
std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    pugi::xml_document doc;
    pugi::xml_parse_result parse_result = doc.load_string(xml_data.c_str());
    
    if (!parse_result) {
        return result;
    }
    
    // XPath를 사용하여 특정 username과 password를 가진 student 찾기
    std::string xpath_query = "/students/student[username='" + username + 
                              "' and password='" + password + "']";
    
    pugi::xpath_node_set students = doc.select_nodes(xpath_query.c_str());
    
    if (students.empty()) {
        return result;
    }
    
    pugi::xpath_node matched_student = students[0];
    pugi::xml_node student_node = matched_student.node();
    
    // 필요한 정보 추출
    result["name"] = student_node.child("name").text().get();
    result["citizenship"] = student_node.child("citizenship").text().get();
    result["age"] = student_node.child("age").text().get();
    
    return result;
}
*/