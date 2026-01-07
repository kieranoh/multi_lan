#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML 데이터를 구문 분석하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음과 같은 구조를 가집니다:
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

XPath 쿼리를 구성하고 이를 사용하여 검색할 수 있습니다.

@param xml_data 학생 정보를 포함하는 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 그렇지 않으면 NULL을 반환합니다. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    if (!xml_data || !username || !password) {
        return NULL;
    }
    
    // XML 데이터 파싱
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (!doc) {
        return NULL;
    }
    
    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 노드 찾기
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval || xpathObj->nodesetval->nodeNr == 0) {
        if (xpathObj) xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    nodes = xpathObj->nodesetval;
    
    // 첫 번째 매칭 노드 가져오기 (username/password 조합은 고유해야 함)
    xmlNodePtr studentNode = nodes->nodeTab[0];
    
    // StudentInfo 구조체 할당
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (!result) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // 초기화
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // student 노드의 자식 노드 순회
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
    
    // 모든 필드가 성공적으로 채워졌는지 확인
    if (!result->name || !result->age || !result->citizenship) {
        // 하나라도 실패하면 메모리 정리
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return result;
}