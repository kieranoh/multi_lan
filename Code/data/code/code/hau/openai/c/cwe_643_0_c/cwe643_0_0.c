#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    // XML 데이터를 파서 초기화
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // 오류가 발생하면 NULL 반환
    }
    
    // XPath 컨텍스트 생성
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // 오류가 발생하면 NULL 반환
    }

    // XPath 쿼리 구성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);

    // XPath 쿼리 실행
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 학생을 찾을 수 없으면 NULL 반환
    }

    // 학생 정보를 가져오기
    StudentInfo* student = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 메모리 할당 오류
    }

    // 학생 노드 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // 이름, 시민권, 나이 가져오기
    student->name = (char*)xmlNodeGetContent(xmlNodeGetChild(studentNode, 2));
    student->citizenship = (char*)xmlNodeGetContent(xmlNodeGetChild(studentNode, 3));
    student->age = (char*)xmlNodeGetContent(xmlNodeGetChild(studentNode, 4));

    // 메모리 해제
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student; // 학생 정보 반환
}