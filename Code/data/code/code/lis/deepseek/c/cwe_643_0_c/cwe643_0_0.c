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
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // XML 데이터 파싱
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }
    
    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
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
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // 학생을 찾지 못함
        goto cleanup;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // StudentInfo 구조체 할당
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // 초기화
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // student 노드의 자식 노드 순회
    xmlNodePtr child = studentNode->children;
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
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
    
    // 모든 필드가 채워졌는지 확인
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // 필드가 누락되었으므로 메모리 정리
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // 리소스 정리
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    return result;
}