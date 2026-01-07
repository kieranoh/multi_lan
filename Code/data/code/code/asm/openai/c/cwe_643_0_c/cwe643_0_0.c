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
    snprintf(xpath_query, sizeof(xpath_query), "//student[username='%s' and password='%s']", username, password);
    
    // XPath 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // 학생 정보 추출
    student_info = malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생의 이름, 나이, 시민권 정보를 추출
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"name", xpathCtx);
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"age", xpathCtx);
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"citizenship", xpathCtx);

    student_info->name = (nameNode != NULL) ? (char *)xmlNodeGetContent(nameNode) : NULL;
    student_info->age = (ageNode != NULL) ? (char *)xmlNodeGetContent(ageNode) : NULL;
    student_info->citizenship = (citizenshipNode != NULL) ? (char *)xmlNodeGetContent(citizenshipNode) : NULL;

    // 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}