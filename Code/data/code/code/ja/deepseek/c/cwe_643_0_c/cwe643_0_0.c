#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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
    if (!xml_data || !username || !password) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;

    // XMLドキュメントをメモリから解析
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (!doc) {
        goto cleanup;
    }

    // XPathコンテキストを作成
    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        goto cleanup;
    }

    // XPathクエリを構築
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);

    // XPathクエリを実行
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (!xpathObj || xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        goto cleanup;
    }

    // 最初のマッチするノードを取得
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // StudentInfo構造体を割り当て
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (!result) {
        goto cleanup;
    }
    
    // メンバーをNULLで初期化
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;

    // 子ノードを走査して情報を抽出
    xmlNodePtr child = studentNode->children;
    while (child) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content) {
                if (strcmp((const char*)child->name, "name") == 0) {
                    result->name = strdup((const char*)content);
                } else if (strcmp((const char*)child->name, "age") == 0) {
                    result->age = strdup((const char*)content);
                } else if (strcmp((const char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup((const char*)content);
                }
                xmlFree(content);
            }
        }
        child = child->next;
    }

    // すべての必須フィールドが抽出されたか確認
    if (!result->name || !result->age || !result->citizenship) {
        // メモリを解放
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    if (xpathObj) xmlXPathFreeObject(xpathObj);
    if (xpathCtx) xmlXPathFreeContext(xpathCtx);
    if (doc) xmlFreeDoc(doc);
    
    return result;
}