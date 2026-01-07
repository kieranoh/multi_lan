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

@param xml_data 학생 정보를 포함하는 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 그렇지 않으면 NULL을 반환합니다. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpath_ctx;
    xmlXPathObjectPtr xpath_obj;
    StudentInfo* student_info = NULL;

    // XML 데이터 파싱
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL; // XML 파싱 실패
    }

    // XPath 컨텍스트 초기화
    xpath_ctx = xmlXPathNewContext(doc);
    if (xpath_ctx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // XPath 컨텍스트 생성 실패
    }

    // XPath 쿼리 생성
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);
    
    xpath_obj = xmlXPathEvalExpression((xmlChar *)xpath_query, xpath_ctx);
    if (xpath_obj == NULL || xpath_obj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        return NULL; // 학생 정보를 찾지 못함
    }

    // 학생 정보 할당
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        return NULL; // 메모리 할당 실패
    }

    // 정보 추출
    xmlNodePtr student_node = xpath_obj->nodesetval->nodeTab[0];
    student_info->name = (char*)xmlNodeGetContent(xmlGetFirstChild(student_node));
    student_info->citizenship = (char*)xmlXPathEvalExpression((xmlChar *)"citizenship", xpath_ctx)->nodesetval->nodeTab[0]->content;
    student_info->age = (char*)xmlXPathEvalExpression((xmlChar *)"age", xpath_ctx)->nodesetval->nodeTab[0]->content;

    // 메모리 해제
    xmlXPathFreeObject(xpath_obj);
    xmlXPathFreeContext(xpath_ctx);
    xmlFreeDoc(doc);

    return student_info; // 학생 정보 반환
}