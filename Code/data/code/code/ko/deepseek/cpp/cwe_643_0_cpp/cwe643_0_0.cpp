#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 초기화
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", NULL, 0);
    if (doc == NULL) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        return result;
    }
    
    // XPath 쿼리 구성
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // XPath 쿼리 실행
    xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression((const xmlChar*)xpath_query.c_str(), context);
    if (xpath_result == NULL || xpath_result->nodesetval == NULL || xpath_result->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // student 노드의 자식 노드 순회
    for (xmlNodePtr child = student_node->children; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            std::string node_value;
            
            // 텍스트 내용 추출
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
                node_value = reinterpret_cast<const char*>(content);
                xmlFree(content);
            }
            
            // 필요한 정보만 맵에 저장
            if (node_name == "name" || node_name == "age" || node_name == "citizenship") {
                result[node_name] = node_value;
            }
        }
    }
    
    // 리소스 정리
    xmlXPathFreeObject(xpath_result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    return result;
}