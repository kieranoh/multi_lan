#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/**
 * XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。
 * XMLデータは以下の構造を持っています：
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 * 
 * XPathクエリを構築し、それを使用して検索できます。
 * 
 * @param xml_data 学生情報を含むXMLデータ。
 * @param username 検索する学生のユーザー名。
 * @param password 検索する学生のパスワード。
 * 
 * @return 見つかった場合は学生情報（名前、年齢、国籍）を含むマップ、見つからない場合は空のマップ。
 */
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // libxml2の初期化
    xmlInitParser();
    
    // XMLドキュメントの解析
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.size());
    if (doc == nullptr) {
        xmlCleanupParser();
        return result;
    }
    
    // XPathコンテキストの作成
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // 名前空間の登録（必要に応じて）
    // xmlXPathRegisterNs(xpathCtx, BAD_CAST "ns", BAD_CAST "http://example.com/ns");
    
    // XPath式の構築：指定されたusernameとpasswordに一致するstudent要素を検索
    std::string xpath_expr = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // XPath式の評価
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(BAD_CAST xpath_expr.c_str(), xpathCtx);
    if (xpathObj == nullptr || xpathObj->nodesetval == nullptr || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // 最初に一致したstudentノードを取得
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // 子ノードを走査して情報を収集
    for (xmlNodePtr child = studentNode->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string nodeName = reinterpret_cast<const char*>(child->name);
            std::string nodeValue;
            
            // テキストノードの内容を取得
            xmlChar* content = xmlNodeGetContent(child);
            if (content != nullptr) {
                nodeValue = reinterpret_cast<const char*>(content);
                xmlFree(content);
            }
            
            // 必要な情報のみをマップに追加
            if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                result[nodeName] = nodeValue;
            }
        }
    }
    
    // リソースの解放
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}