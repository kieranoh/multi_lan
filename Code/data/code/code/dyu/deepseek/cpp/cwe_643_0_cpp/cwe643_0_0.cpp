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
    xmlInitParser();
    
    // 메모리에서 XML 파싱
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", NULL, 0);
    if (doc == NULL) {
        xmlCleanupParser();
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // XPath 쿼리 구성: 주어진 사용자명과 비밀번호에 해당하는 student 노드 찾기
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // XPath 쿼리 실행
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query.c_str(), xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // 첫 번째 매칭 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // 자식 노드 순회하며 정보 수집
    for (xmlNodePtr child = studentNode->children; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string nodeName = reinterpret_cast<const char*>(child->name);
            xmlChar* content = xmlNodeGetContent(child);
            
            if (content != NULL) {
                std::string nodeValue = reinterpret_cast<const char*>(content);
                
                // 필요한 정보만 맵에 추가
                if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                    result[nodeName] = nodeValue;
                }
                
                xmlFree(content);
            }
        }
    }
    
    // 리소스 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}