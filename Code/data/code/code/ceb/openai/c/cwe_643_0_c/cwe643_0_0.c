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
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return NULL;
    }

    // Create XPath Context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Failed to create XPath context\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct XPath expression
    char xpath_expr[256];
    snprintf(xpath_expr, sizeof(xpath_expr), "/students/student[username='%s' and password='%s']", username, password);
    
    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_expr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract student information
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        fprintf(stderr, "Failed to allocate memory for StudentInfo\n");
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Get the student node
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // Extract name
    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"name", xpathCtx);
    student_info->name = (char*)xmlNodeGetContent(nameNode);
    
    // Extract citizenship
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"citizenship", xpathCtx);
    student_info->citizenship = (char*)xmlNodeGetContent(citizenshipNode);
    
    // Extract age
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"age", xpathCtx);
    student_info->age = (char*)xmlNodeGetContent(ageNode);

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}