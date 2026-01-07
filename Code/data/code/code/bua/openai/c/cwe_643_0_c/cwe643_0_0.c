#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdio.h>
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

    // XML 데이터 파싱
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return NULL;
    }

    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Failed to create XPath context\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath 쿼리 구성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query),
             "//student[username='%s' and password='%s']", username, password);

    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "Failed to evaluate XPath expression\n");
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생 정보가 발견된 경우
    if (xpathObj->nodesetval->nodeNr > 0) {
        student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
        if (student_info == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL;
        }

        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        student_info->name = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"name", xpathCtx));
        student_info->age = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"age", xpathCtx));
        student_info->citizenship = (char*)xmlNodeGetContent(xmlXPathNodeEval(studentNode, (const xmlChar*)"citizenship", xpathCtx));
    }

    // 리소스 해제
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}