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

XPath 쿼리를 구성하여 검색에 사용할 수 있습니다.

@param xml_data 학생 정보를 포함하는 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 StudentInfo 구조체에 대한 포인터를 반환합니다. 그렇지 않으면 NULL을 반환합니다. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Failed to parse XML
    }

    // Create XPath context
    context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Failed to create XPath context
    }

    // Create the XPath expression
    char xpath_expr[256];
    snprintf(xpath_expr, sizeof(xpath_expr), 
             "//student[username='%s' and password='%s']", username, password);
    
    // Evaluate the XPath expression
    result = xmlXPathEvalExpression((const xmlChar*)xpath_expr, context);
    if (result == NULL || xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return NULL; // No matching student found
    }

    // Get the first matching student node
    xmlNodePtr student_node = result->nodesetval->nodeTab[0];

    // Allocate memory for StudentInfo
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failed
    }

    // Extract student information
    for (xmlNodePtr curr = student_node->children; curr != NULL; curr = curr->next) {
        if (curr->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curr->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(curr);
            } else if (xmlStrcmp(curr->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(curr);
            } else if (xmlStrcmp(curr->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(curr);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    
    return student_info; // Return the filled StudentInfo structure
}