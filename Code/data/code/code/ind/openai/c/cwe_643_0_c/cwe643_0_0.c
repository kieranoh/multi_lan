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

    // XPath 쿼리 구성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "/students/student[username='%s' and password='%s']", 
             username, password);

    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생 정보 추출
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr node = student_node->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(node->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(node);
            } else if (xmlStrcmp(node->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(node);
            } else if (xmlStrcmp(node->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(node);
            }
        }
    }

    // 메모리 해제
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}