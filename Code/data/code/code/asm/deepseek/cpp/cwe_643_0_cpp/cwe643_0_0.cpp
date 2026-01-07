#include <map>
#include <string>
#include <memory>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 파싱
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", nullptr, 0);
    if (doc == nullptr) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        xmlFreeDoc(doc);
        return result;
    }
    
    // XPath 쿼리 구성: username과 password가 일치하는 student 요소 찾기
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // XPath 평가 실행
    xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context);
    if (xpath_result == nullptr || xpath_result->nodesetval == nullptr || xpath_result->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // student 노드의 자식 요소들을 순회하며 정보 수집
    for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            if (node_name == "name" || node_name == "age" || node_name == "citizenship") {
                xmlChar* content = xmlNodeGetContent(child);
                if (content != nullptr) {
                    result[node_name] = reinterpret_cast<const char*>(content);
                    xmlFree(content);
                }
            }
        }
    }
    
    // 리소스 정리
    xmlXPathFreeObject(xpath_result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    return result;
}