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
    
    // XPath 쿼리 구성: username과 password가 일치하는 student 요소 찾기
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // 학생을 찾지 못함
        if (xpathObj != NULL) {
            xmlXPathFreeObject(xpathObj);
        }
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // 첫 번째 일치하는 student 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // StudentInfo 구조체 할당
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // 초기화
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // student 노드의 자식 요소 순회
    xmlNodePtr child = studentNode->children;
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
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
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // 필드가 하나라도 없으면 메모리 해제하고 NULL 반환
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // 리소스 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return result;
}

/* 참고: 이 함수를 사용하는 쪽에서 반환된 StudentInfo 구조체의 메모리를 해제해야 합니다.
void free_student_info(StudentInfo* info) {
    if (info != NULL) {
        free(info->name);
        free(info->age);
        free(info->citizenship);
        free(info);
    }
}
*/