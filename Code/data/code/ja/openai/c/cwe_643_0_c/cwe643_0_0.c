#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。XMLデータは以下の構造を持っています：
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>John Doe</name>
        <citizenship>USA</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>Bob Smith</name>
        <citizenship>Canada</citizenship>
        <age>22</age>
    </student>
</students>

XPathクエリを構築し、それを使用して検索できます。

@param xml_data 学生情報を含むXMLデータ。
@param username 検索する学生のユーザー名。
@param password 検索する学生のパスワード。

@return 学生が見つかった場合はStudentInfo構造体へのポインタを返します。見つからない場合はNULLを返します。 */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // XMLデータを解析
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // パースエラー
    }

    // XPathコンテキストを作成
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // コンテキストエラー
    }

    // XPathクエリを構築
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);

    // XPathクエリを評価
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 学生が見つからない
    }

    // 学生情報を取得
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // メモリ割り当てエラー
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    student_info->name = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"name", xpathCtx));
    student_info->age = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"age", xpathCtx));
    student_info->citizenship = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"citizenship", xpathCtx));

    // 後片付け
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // 学生情報を返す
}