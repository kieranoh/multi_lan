#include <map>
#include <string>
#include <vector>
#include <memory>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/parser.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 파싱
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", nullptr, 0);
    if (!doc) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (!context) {
        xmlFreeDoc(doc);
        return result;
    }
    
    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 노드 찾기
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // XPath 쿼리 실행
    xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context);
    if (!xpath_result || !xpath_result->nodesetval || xpath_result->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // student 노드의 자식 노드 순회
    for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            
            // name, citizenship, age 노드의 내용 추출
            if (node_name == "name" || node_name == "citizenship" || node_name == "age") {
                xmlChar* content = xmlNodeGetContent(child);
                if (content) {
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