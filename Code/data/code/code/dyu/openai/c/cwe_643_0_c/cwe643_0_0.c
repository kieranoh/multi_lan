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
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // XML 파서 초기화
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // XPath 컨텍스트 만들기
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath 쿼리 작성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);

    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생 정보를 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    student_info->name = (char*)xmlNodeGetContent(xmlXPathEvalExpression((const xmlChar*)"name", xpathCtx)->nodesetval->nodeTab[0]);
    student_info->age = (char*)xmlNodeGetContent(xmlXPathEvalExpression((const xmlChar*)"age", xpathCtx)->nodesetval->nodeTab[0]);
    student_info->citizenship = (char*)xmlNodeGetContent(xmlXPathEvalExpression((const xmlChar*)"citizenship", xpathCtx)->nodesetval->nodeTab[0]);

    // 메모리 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}