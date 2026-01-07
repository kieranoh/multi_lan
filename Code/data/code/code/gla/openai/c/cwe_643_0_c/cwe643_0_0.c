#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음과 같은 구조를 가집니다:
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>John Doe</name>
        <citizenship>USA</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>Bob Smith</name>
        <citizenship>Canada</citizenship>
        <age>22</age>
    </student>
</students>

XPath 쿼리를 구성하고 이를 사용하여 검색할 수 있습니다.

@param xml_data 학생 정보를 포함하는 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 그렇지 않으면 NULL을 반환합니다. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* studentInfo = NULL;

    // XML 데이터를 파싱합니다.
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // 파싱 실패
    }

    // XPath 컨텍스트를 설정합니다.
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // 컨텍스트 생성 실패
    }

    // XPath 쿼리를 구성하여 특정 학생 정보를 검색합니다.
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "//student[username='%s' and password='%s']", username, password);

    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 학생 정보를 찾지 못함
    }

    // 학생 정보를 추출합니다.
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 메모리 할당 실패
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // 이름, 시민권, 나이 정보를 가져옵니다.
    for (xmlNodePtr currentNode = studentNode->children; currentNode; currentNode = currentNode->next) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(currentNode->name, (const xmlChar *)"name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(currentNode);
            } else if (xmlStrcmp(currentNode->name, (const xmlChar *)"citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(currentNode);
            } else if (xmlStrcmp(currentNode->name, (const xmlChar *)"age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(currentNode);
            }
        }
    }

    // 메모리 해제를 위한 클린업
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; // 학생 정보를 반환
}