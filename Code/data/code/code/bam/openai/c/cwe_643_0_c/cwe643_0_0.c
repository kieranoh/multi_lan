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
    StudentInfo* studentInfo = NULL;

    // XML 문서 파싱
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL; // XML 파싱 실패
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // XPath 컨텍스트 생성 실패
    }

    // XPath 쿼리: 사용자 이름과 비밀번호로 학생 정보 검색
    char xpathQuery[256];
    snprintf(xpathQuery, sizeof(xpathQuery), 
             "//student[username='%s' and password='%s']", 
             username, password);

    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 학생 정보 없음
    }

    // 학생 정보가 발견된 경우
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 메모리 할당 실패
    }

    // 학생 정보 추출
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr currNode = studentNode->children; currNode; currNode = currNode->next) {
        if (currNode->type == XML_ELEMENT_NODE) {
            if (strcmp((const char*)currNode->name, "name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(currNode);
            } else if (strcmp((const char*)currNode->name, "age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(currNode);
            } else if (strcmp((const char*)currNode->name, "citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(currNode);
            }
        }
    }

    // 메모리 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; // 학생 정보 반환
}