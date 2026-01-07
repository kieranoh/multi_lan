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

    // XML 문서를 메모리에서 파싱
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (!doc) {
        goto cleanup;
    }

    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        goto cleanup;
    }

    // 사용자 이름과 비밀번호로 학생 찾기 위한 XPath 쿼리 구성
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);

    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }

    // 첫 번째 매칭 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // 결과 구조체 할당
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (!result) {
        goto cleanup;
    }
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;

    // 자식 노드를 순회하며 정보 추출
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
    if (xpathObj) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc) {
        xmlFreeDoc(doc);
    }
    xmlCleanupParser();

    return result;
}