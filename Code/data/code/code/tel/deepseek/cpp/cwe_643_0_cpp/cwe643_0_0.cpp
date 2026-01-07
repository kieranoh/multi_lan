#include <map>
#include <string>
#include <vector>
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
    
    // 네임스페이스 등록 (사용하지 않음)
    // xmlXPathRegisterNs(context, BAD_CAST "ns", BAD_CAST "http://example.com");
    
    // XPath 표현식: username과 password가 일치하는 student 요소 찾기
    std::string xpath_expr = "/students/student[username='" + username + "' and password='" + password + "']";
    xmlXPathObjectPtr xpath_obj = xmlXPathEvalExpression(BAD_CAST xpath_expr.c_str(), context);
    
    if (xpath_obj == nullptr || xpath_obj->nodesetval == nullptr || xpath_obj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr student_node = xpath_obj->nodesetval->nodeTab[0];
    
    // student 노드의 자식 요소들을 순회하며 정보 수집
    for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            
            // username과 password는 결과에 포함하지 않음
            if (node_name == "username" || node_name == "password") {
                continue;
            }
            
            // 요소의 텍스트 내용 가져오기
            xmlChar* content = xmlNodeGetContent(child);
            if (content != nullptr) {
                result[node_name] = reinterpret_cast<const char*>(content);
                xmlFree(content);
            }
        }
    }
    
    // 리소스 정리
    xmlXPathFreeObject(xpath_obj);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    return result;
}