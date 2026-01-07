#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

// libxml2 헤더
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // libxml2 초기화
    xmlInitParser();
    
    // XML 데이터 파싱
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.length());
    if (doc == nullptr) {
        xmlCleanupParser();
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    try {
        // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
        std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
        
        // XPath 쿼리 실행
        xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context);
        if (xpath_result == nullptr) {
            xmlXPathFreeContext(context);
            xmlFreeDoc(doc);
            xmlCleanupParser();
            return result;
        }
        
        // 결과 노드셋 확인
        if (xpath_result->type == XPATH_NODESET && xpath_result->nodesetval != nullptr) {
            xmlNodeSetPtr nodeset = xpath_result->nodesetval;
            
            // 일치하는 학생이 있는 경우
            if (nodeset->nodeNr > 0) {
                xmlNodePtr student_node = nodeset->nodeTab[0];
                
                // 자식 노드 순회하며 정보 추출
                for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
                    if (child->type == XML_ELEMENT_NODE) {
                        std::string node_name = reinterpret_cast<const char*>(child->name);
                        
                        // username과 password는 결과에 포함하지 않음
                        if (node_name == "name" || node_name == "citizenship" || node_name == "age") {
                            xmlChar* content = xmlNodeGetContent(child);
                            if (content != nullptr) {
                                result[node_name] = reinterpret_cast<const char*>(content);
                                xmlFree(content);
                            }
                        }
                    }
                }
            }
        }
        
        // XPath 결과 메모리 해제
        xmlXPathFreeObject(xpath_result);
        
    } catch (...) {
        // 예외 발생 시 정리
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // 리소스 정리
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}