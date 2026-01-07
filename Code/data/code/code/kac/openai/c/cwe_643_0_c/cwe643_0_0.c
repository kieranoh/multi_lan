#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. 
   XML 데이터는 다음과 같은 구조를 가집니다:
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

   @return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 
           그렇지 않으면 NULL을 반환합니다. */
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

    // XPath 쿼리 작성 (username과 password를 포함)
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "/students/student[username='%s' and password='%s']", 
             username, password);

    // XPath 실행
    xpathObj = xmlXPathEvalExpression((xmlChar *)xpath_query, xpathCtx);
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

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // 이름, 시민권, 나이 추출
    for (xmlNodePtr node = studentNode->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(node->name, (const xmlChar *)"name") == 0) {
                student_info->name = strdup((const char *)xmlNodeGetContent(node));
            } else if (xmlStrcmp(node->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = strdup((const char *)xmlNodeGetContent(node));
            } else if (xmlStrcmp(node->name, (const xmlChar *)"age") == 0) {
                student_info->age = strdup((const char *)xmlNodeGetContent(node));
            }
        }
    }

    // 메모리 정리
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}