#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* 解析 XML 数据并返回给定用户名和密码的学生信息。XML 数据将具有以下结构：
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

我们可以构建一个 XPath 查询并使用它进行搜索。

@param xml_data 包含学生信息的 XML 数据。
@param username 要搜索的学生的用户名。
@param password 要搜索的学生的密码。

@return 如果找到学生，则返回指向 StudentInfo 结构的指针。否则，返回 NULL。 */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Failed to parse XML
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Failed to create XPath context
    }

    // Construct XPath expression
    char xpath_expr[256];
    snprintf(xpath_expr, sizeof(xpath_expr), 
             "/students/student[username='%s' and password='%s']", 
             username, password);

    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_expr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No matching student found
    }

    // Allocate memory for StudentInfo
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failed
    }

    // Extract student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr currNode = studentNode->children; currNode; currNode = currNode->next) {
        if (currNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(currNode->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(currNode);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return student_info; // Return the populated StudentInfo structure
}