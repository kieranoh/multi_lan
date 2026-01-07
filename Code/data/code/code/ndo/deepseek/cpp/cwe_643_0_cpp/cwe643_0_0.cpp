#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

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
    
    try {
        // XPath 쿼리 구성: username과 password가 일치하는 student 노드 찾기
        std::string xpath_query = 
            "/students/student[username/text()='" + username + 
            "' and password/text()='" + password + "']";
        
        // XPath 평가
        xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(
            reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context);
        
        if (!xpath_result) {
            xmlXPathFreeContext(context);
            xmlFreeDoc(doc);
            return result;
        }
        
        // 결과 노드셋 확인
        if (xpath_result->type == XPATH_NODESET && 
            xpath_result->nodesetval && 
            xpath_result->nodesetval->nodeNr > 0) {
            
            xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
            
            // 자식 노드 순회하며 정보 추출
            for (xmlNodePtr child = student_node->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    std::string node_name = reinterpret_cast<const char*>(child->name);
                    
                    // 필요한 정보만 추출 (name, citizenship, age)
                    if (node_name == "name" || node_name == "citizenship" || node_name == "age") {
                        xmlChar* content = xmlNodeGetContent(child);
                        if (content) {
                            result[node_name] = reinterpret_cast<const char*>(content);
                            xmlFree(content);
                        }
                    }
                }
            }
        }
        
        // XPath 결과 정리
        xmlXPathFreeObject(xpath_result);
        
    } catch (...) {
        // 예외 발생 시 정리
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 정리
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    return result;
}