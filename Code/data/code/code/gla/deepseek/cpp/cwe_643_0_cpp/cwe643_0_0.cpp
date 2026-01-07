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
    
    // XML 문서 초기화
    xmlInitParser();
    
    // 메모리에서 XML 파싱
    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc(
        xmlReadMemory(xml_data.c_str(), xml_data.size(), nullptr, nullptr, 0),
        xmlFreeDoc
    );
    
    if (!doc) {
        xmlCleanupParser();
        return result;
    }
    
    // XPath 컨텍스트 생성
    std::unique_ptr<xmlXPathContext, decltype(&xmlXPathFreeContext)> context(
        xmlXPathNewContext(doc.get()),
        xmlXPathFreeContext
    );
    
    if (!context) {
        xmlCleanupParser();
        return result;
    }
    
    try {
        // XPath 쿼리 구성: 주어진 username과 password를 가진 student 노드 찾기
        std::string xpath_query = 
            "/students/student[username/text()='" + username + 
            "' and password/text()='" + password + "']";
        
        // XPath 평가
        std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> xpath_result(
            xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context.get()),
            xmlXPathFreeObject
        );
        
        if (!xpath_result || xpath_result->nodesetval == nullptr || 
            xpath_result->nodesetval->nodeNr == 0) {
            xmlCleanupParser();
            return result;
        }
        
        // 첫 번째 매칭 노드 가져오기
        xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
        
        // 자식 노드 순회하며 정보 수집
        for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string node_name = reinterpret_cast<const char*>(child->name);
                
                // username과 password는 결과에 포함하지 않음
                if (node_name == "username" || node_name == "password") {
                    continue;
                }
                
                // 텍스트 내용 가져오기
                xmlChar* content = xmlNodeGetContent(child);
                if (content) {
                    result[node_name] = reinterpret_cast<const char*>(content);
                    xmlFree(content);
                }
            }
        }
        
    } catch (...) {
        // 예외 발생 시 정리
        xmlCleanupParser();
        throw;
    }
    
    xmlCleanupParser();
    return result;
}