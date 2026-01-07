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
    // XML 파서와 XPath 객체 초기화
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath 쿼리 구성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), "/students/student[username='%s' and password='%s']", username, password);

    // XPath 실행
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 첫 번째 일치하는 학생 정보 가져오기
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    StudentInfo* student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // 학생의 이름, 시민권 및 나이를 추출
    xmlNodePtr currentNode = studentNode->children;
    while (currentNode) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(currentNode->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char *)xmlNodeGetContent(currentNode);
            } else if (xmlStrcmp(currentNode->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char *)xmlNodeGetContent(currentNode);
            } else if (xmlStrcmp(currentNode->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char *)xmlNodeGetContent(currentNode);
            }
        }
        currentNode = currentNode->next;
    }

    // 메모리 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}