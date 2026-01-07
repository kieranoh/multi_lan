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
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL; // Parsing error
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // XPath context creation error
    }

    // Create XPath expression
    char xpath_expression[256];
    snprintf(xpath_expression, sizeof(xpath_expression), 
             "/students/student[username='%s' and password='%s']", username, password);

    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expression, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No matching student found
    }

    // Assuming we are interested in the first matching student
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // Allocate memory for StudentInfo
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation error
    }

    // Extract student information
    for (xmlNodePtr child = studentNode->children; child; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(child->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(child);
            } else if (xmlStrcmp(child->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(child);
            } else if (xmlStrcmp(child->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(child);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the populated StudentInfo structure
}