#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>
#include <libxml/parser.h>

// RAII 래퍼 클래스들
class XmlDocDeleter {
public:
    void operator()(xmlDocPtr doc) const {
        if (doc) xmlFreeDoc(doc);
    }
};

class XmlXPathContextDeleter {
public:
    void operator()(xmlXPathContextPtr context) const {
        if (context) xmlXPathFreeContext(context);
    }
};

class XmlXPathObjectDeleter {
public:
    void operator()(xmlXPathObjectPtr object) const {
        if (object) xmlXPathFreeObject(object);
    }
};

using XmlDocPtr = std::unique_ptr<xmlDoc, XmlDocDeleter>;
using XmlXPathContextPtr = std::unique_ptr<xmlXPathContext, XmlXPathContextDeleter>;
using XmlXPathObjectPtr = std::unique_ptr<xmlXPathObject, XmlXPathObjectDeleter>;

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // XML 파싱
    XmlDocPtr doc(xmlParseMemory(xml_data.c_str(), xml_data.length()));
    if (!doc) {
        return result;
    }
    
    // XPath 컨텍스트 생성
    XmlXPathContextPtr context(xmlXPathNewContext(doc.get()));
    if (!context) {
        return result;
    }
    
    // XPath 쿼리 구성
    std::string xpath_query = 
        "/students/student[username='" + username + 
        "' and password='" + password + "']";
    
    // XPath 평가
    XmlXPathObjectPtr xpath_result(
        xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), 
                              context.get()));
    
    if (!xpath_result || xpath_result->nodesetval == nullptr || 
        xpath_result->nodesetval->nodeNr == 0) {
        return result;
    }
    
    // 첫 번째 매칭 노드 가져오기
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // 필요한 정보 추출
    auto get_node_text = [](xmlNodePtr parent, const char* child_name) -> std::string {
        if (!parent) return "";
        
        for (xmlNodePtr child = parent->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE && 
                xmlStrcmp(child->name, reinterpret_cast<const xmlChar*>(child_name)) == 0) {
                xmlChar* content = xmlNodeGetContent(child);
                if (content) {
                    std::string result(reinterpret_cast<const char*>(content));
                    xmlFree(content);
                    return result;
                }
                return "";
            }
        }
        return "";
    };
    
    // 정보 수집
    std::string name = get_node_text(student_node, "name");
    std::string citizenship = get_node_text(student_node, "citizenship");
    std::string age = get_node_text(student_node, "age");
    
    // 결과 맵 구성
    if (!name.empty()) {
        result["name"] = name;
    }
    if (!citizenship.empty()) {
        result["citizenship"] = citizenship;
    }
    if (!age.empty()) {
        result["age"] = age;
    }
    
    return result;
}