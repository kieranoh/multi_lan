#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/**
 * XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다.
 * 
 * @param xml_data 학생 정보를 포함하는 XML 데이터.
 * @param username 검색할 학생의 사용자 이름.
 * @param password 검색할 학생의 비밀번호.
 * @return 학생 정보(이름, 나이, 시민권)를 포함하는 맵을 반환하며, 찾지 못한 경우 빈 맵을 반환합니다.
 */
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // libxml2 초기화
    xmlInitParser();
    
    // XML 데이터 파싱
    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc(
        xmlParseMemory(xml_data.c_str(), xml_data.size()),
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
    
    // XPath 네임스페이스 등록 (필요한 경우)
    xmlXPathRegisterNs(context.get(), BAD_CAST "ns", BAD_CAST "http://example.com");
    
    // XPath 쿼리 구성: username과 password가 일치하는 student 요소 찾기
    std::string xpath_query = 
        "/students/student[username/text()='" + username + 
        "' and password/text()='" + password + "']";
    
    // XPath 평가
    std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> xpath_result(
        xmlXPathEvalExpression(BAD_CAST xpath_query.c_str(), context.get()),
        xmlXPathFreeObject
    );
    
    if (!xpath_result || xpath_result->type != XPATH_NODESET || 
        !xpath_result->nodesetval || xpath_result->nodesetval->nodeNr == 0) {
        xmlCleanupParser();
        return result;
    }
    
    // 첫 번째 일치하는 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // 학생 정보 추출을 위한 헬퍼 함수
    auto extract_text = [](xmlNodePtr node, const char* child_name) -> std::string {
        if (!node) return "";
        
        for (xmlNodePtr child = node->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE && 
                xmlStrcmp(child->name, BAD_CAST child_name) == 0) {
                xmlChar* content = xmlNodeGetContent(child);
                if (content) {
                    std::string result_str = reinterpret_cast<const char*>(content);
                    xmlFree(content);
                    return result_str;
                }
                return "";
            }
        }
        return "";
    };
    
    // 필요한 정보 추출
    std::string name = extract_text(student_node, "name");
    std::string citizenship = extract_text(student_node, "citizenship");
    std::string age = extract_text(student_node, "age");
    
    // 결과 맵에 추가
    if (!name.empty()) result["name"] = name;
    if (!citizenship.empty()) result["citizenship"] = citizenship;
    if (!age.empty()) result["age"] = age;
    
    // 정리
    xmlCleanupParser();
    
    return result;
}