#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML 데이터를 구문 분석하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음과 같은 구조를 가집니다:
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

@param xml_data 학생 정보를 포함하는 XML 데이터입니다.
@param username 검색할 학생의 사용자 이름입니다.
@param password 검색할 학생의 비밀번호입니다.

@return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 그렇지 않으면 NULL을 반환합니다. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* studentInfo = NULL;

    // XML 데이터 파싱
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // XML 파싱 오류
    }

    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // XPath 컨텍스트 생성 오류
    }

    // XPath 쿼리 구성
    char query[256];
    snprintf(query, sizeof(query), "/students/student[username='%s' and password='%s']", username, password);
    
    // XPath 쿼리 실행
    xpathObj = xmlXPathEvalExpression((const xmlChar*)query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // 학생을 찾지 못함
    }

    // 학생 정보 추출
    xmlNodePtr node = xpathObj->nodesetval->nodeTab[0];
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    
    xmlNodePtr nameNode = xmlXPathNodeEval(node, (const xmlChar*)"name", xpathCtx);
    xmlNodePtr ageNode = xmlXPathNodeEval(node, (const xmlChar*)"age", xpathCtx);
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(node, (const xmlChar*)"citizenship", xpathCtx);

    studentInfo->name = (char*)xmlNodeGetContent(nameNode);
    studentInfo->age = (char*)xmlNodeGetContent(ageNode);
    studentInfo->citizenship = (char*)xmlNodeGetContent(citizenshipNode);

    // 메모리 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; // 학생 정보 반환
}