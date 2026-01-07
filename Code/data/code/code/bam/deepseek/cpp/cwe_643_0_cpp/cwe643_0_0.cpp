#include <map>
#include <string>
#include <memory>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 문서 파싱
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.length());
    if (doc == nullptr) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        xmlFreeDoc(doc);
        return result;
    }
    
    // 네임스페이스 등록 (없는 경우)
    xmlXPathRegisterNs(context, BAD_CAST "ns", BAD_CAST "http://example.com");
    
    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
    std::string xpath_query = 
        "/students/student[username/text()='" + username + 
        "' and password/text()='" + password + "']";
    
    // XPath 쿼리 실행
    xmlXPathObjectPtr xpath_result = xmlXPathEvalExpression(
        BAD_CAST xpath_query.c_str(), context);
    
    if (xpath_result == nullptr || xpath_result->nodesetval == nullptr ||
        xpath_result->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return result;
    }
    
    // 첫 번째 매칭 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // 필요한 정보 추출
    auto extract_text = [](xmlNodePtr parent, const char* child_name) -> std::string {
        for (xmlNodePtr child = parent->children; child != nullptr; child = child->next) {
            if (child->type == XML_ELEMENT_NODE && 
                xmlStrcmp(child->name, BAD_CAST child_name) == 0) {
                xmlChar* content = xmlNodeGetContent(child);
                if (content != nullptr) {
                    std::string text(reinterpret_cast<const char*>(content));
                    xmlFree(content);
                    return text;
                }
            }
        }
        return "";
    };
    
    result["name"] = extract_text(student_node, "name");
    result["age"] = extract_text(student_node, "age");
    result["citizenship"] = extract_text(student_node, "citizenship");
    
    // 리소스 정리
    xmlXPathFreeObject(xpath_result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    // 모든 필드가 비어있는지 확인하고, 비어있다면 빈 맵 반환
    bool all_empty = true;
    for (const auto& pair : result) {
        if (!pair.second.empty()) {
            all_empty = false;
            break;
        }
    }
    
    if (all_empty) {
        result.clear();
    }
    
    return result;
}