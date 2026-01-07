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

    // XPath 쿼리 작성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "/students/student[username='%s' and password='%s']", 
             username, password);

    // XPath 평가
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생 정보 추출
    student_info = malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        fprintf(stderr, "Failed to allocate memory for StudentInfo\n");
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];

    // 이름 추출
    xmlNodePtr name_node = xmlNodeGetContent(xmlXPathNodeEval(student_node, (const xmlChar*)"name", xpathCtx));
    student_info->name = strdup((const char*)name_node);
    xmlFree(name_node);

    // 시민권 추출
    xmlNodePtr citizenship_node = xmlNodeGetContent(xmlXPathNodeEval(student_node, (const xmlChar*)"citizenship", xpathCtx));
    student_info->citizenship = strdup((const char*)citizenship_node);
    xmlFree(citizenship_node);

    // 나이 추출
    xmlNodePtr age_node = xmlNodeGetContent(xmlXPathNodeEval(student_node, (const xmlChar*)"age", xpathCtx));
    student_info->age = strdup((const char*)age_node);
    xmlFree(age_node);

    // 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}