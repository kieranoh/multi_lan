#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>

// libxml2 초기화 및 정리 헬퍼 클래스
class LibXMLInitializer {
public:
    LibXMLInitializer() {
        xmlInitParser();
        LIBXML_TEST_VERSION
    }
    
    ~LibXMLInitializer() {
        xmlCleanupParser();
    }
    
    // 복사 방지
    LibXMLInitializer(const LibXMLInitializer&) = delete;
    LibXMLInitializer& operator=(const LibXMLInitializer&) = delete;
};

// XML 문서 자동 관리 클래스
class XmlDocDeleter {
public:
    void operator()(xmlDoc* doc) const {
        if (doc) {
            xmlFreeDoc(doc);
        }
    }
};

using XmlDocPtr = std::unique_ptr<xmlDoc, XmlDocDeleter>;

// XPath 컨텍스트 자동 관리 클래스
class XPathContextDeleter {
public:
    void operator()(xmlXPathContext* ctx) const {
        if (ctx) {
            xmlXPathFreeContext(ctx);
        }
    }
};

using XPathContextPtr = std::unique_ptr<xmlXPathContext, XPathContextDeleter>;

// XPath 객체 자동 관리 클래스
class XPathObjectDeleter {
public:
    void operator()(xmlXPathObject* obj) const {
        if (obj) {
            xmlXPathFreeObject(obj);
        }
    }
};

using XPathObjectPtr = std::unique_ptr<xmlXPathObject, XPathObjectDeleter>;

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // libxml2 초기화
    static LibXMLInitializer init;
    
    if (xml_data.empty() || username.empty() || password.empty()) {
        return result;
    }
    
    // XML 문서 파싱
    XmlDocPtr doc(xmlParseMemory(xml_data.c_str(), static_cast<int>(xml_data.size())));
    if (!doc) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    XPathContextPtr context(xmlXPathNewContext(doc.get()));
    if (!context) {
        return result;
    }
    
    try {
        // XPath 쿼리 구성 - username과 password가 모두 일치하는 student 요소 찾기
        std::string xpath_query = 
            "/students/student[username/text()='" + username + 
            "' and password/text()='" + password + "']";
        
        // XPath 평가
        XPathObjectPtr xpath_result(
            xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), 
                                  context.get())
        );
        
        if (!xpath_result || !xpath_result->nodesetval || xpath_result->nodesetval->nodeNr == 0) {
            return result;
        }
        
        // 첫 번째 일치하는 student 노드 가져오기
        xmlNode* student_node = xpath_result->nodesetval->nodeTab[0];
        
        // 필요한 정보 추출
        std::vector<std::string> fields = {"name", "age", "citizenship"};
        
        for (const auto& field : fields) {
            // 각 필드에 대한 XPath 쿼리
            std::string field_xpath = field + "/text()";
            XPathObjectPtr field_result(
                xmlXPathNodeEval(student_node, 
                                reinterpret_cast<const xmlChar*>(field_xpath.c_str()), 
                                context.get())
            );
            
            if (field_result && field_result->nodesetval && 
                field_result->nodesetval->nodeNr > 0) {
                xmlNode* text_node = field_result->nodesetval->nodeTab[0];
                if (text_node->content) {
                    result[field] = reinterpret_cast<const char*>(text_node->content);
                }
            }
        }
        
    } catch (...) {
        // 예외 발생 시 빈 맵 반환
        result.clear();
    }
    
    return result;
}