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

    // Construct the XPath query for the student
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query),
             "//student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No student found
    }

    // Create a new StudentInfo structure
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failed
    }

    // Extract student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    student_info->name = (char*)xmlNodeGetContent(xmlFirstElementChild(studentNode));
    student_info->citizenship = (char*)xmlNodeGetContent(xmlNextElementSibling(studentNode));
    student_info->age = (char*)xmlNodeGetContent(xmlNextElementSibling(xmlNextElementSibling(studentNode)));

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the found student info
}