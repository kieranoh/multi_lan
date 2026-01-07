#include <map>
#include <string>
#include <vector>
#include <memory>
#include <libxml/xpath.h>
#include <libxml/parser.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 파싱
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.length(), 
                                  "noname.xml", NULL, 0);
    if (doc == NULL) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        return result;
    }
    
    // XPath 쿼리 구성: username과 password가 일치하는 student 요소 찾기
    std::string xpath_query = "/students/student[username='" + username + 
                              "' and password='" + password + "']";
    
    // XPath 평가
    xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(
        (const xmlChar*)xpath_query.c_str(), context);
    
    if (xpath_result == NULL || xpath_result->nodesetval == NULL || 
        xpath_result->nodesetval->nodeNr == 0) {
        // 결과가 없으면 빈 맵 반환
        xmlXPathFreeObject(xpath_result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // student 노드의 자식 요소들을 순회하며 정보 추출
    for (xmlNodePtr child = student_node->children; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = (const char*)child->name;
            
            // username과 password는 결과에 포함하지 않음
            if (node_name == "name" || node_name == "age" || node_name == "citizenship") {
                xmlChar* content = xmlNodeGetContent(child);
                if (content != NULL) {
                    result[node_name] = (const char*)content;
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