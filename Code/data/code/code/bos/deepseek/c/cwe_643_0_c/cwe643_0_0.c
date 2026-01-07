#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    if (!xml_data || !username || !password) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;

    // XML 데이터 파싱
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (!doc) {
        goto cleanup;
    }

    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        goto cleanup;
    }

    // XPath 쿼리 구성: username과 password가 일치하는 student 요소 찾기
    char xpathQuery[512];
    snprintf(xpathQuery, sizeof(xpathQuery),
             "/students/student[username='%s' and password='%s']",
             username, password);

    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }

    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // StudentInfo 구조체 할당
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (!result) {
        goto cleanup;
    }
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;

    // 자식 노드 순회하며 정보 추출
    xmlNodePtr child = studentNode->children;
    while (child) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content) {
                if (strcmp((char*)child->name, "name") == 0) {
                    result->name = strdup((char*)content);
                } else if (strcmp((char*)child->name, "age") == 0) {
                    result->age = strdup((char*)content);
                } else if (strcmp((char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup((char*)content);
                }
                xmlFree(content);
            }
        }
        child = child->next;
    }

    // 모든 필드가 채워졌는지 확인
    if (!result->name || !result->age || !result->citizenship) {
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    if (xpathObj) xmlXPathFreeObject(xpathObj);
    if (xpathCtx) xmlXPathFreeContext(xpathCtx);
    if (doc) xmlFreeDoc(doc);
    
    return result;
}