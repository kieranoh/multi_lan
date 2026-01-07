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

    // Create the XPath expression to find the student
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "//student[username='%s' and password='%s']", username, password);
    
    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Failed to evaluate XPath expression
    }

    // Check if a student was found
    if (xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No student found
    }

    // Extract student info
    StudentInfo* studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failed
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Get name
    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"name", xpathCtx);
    studentInfo->name = (char*)xmlNodeGetContent(nameNode);
    
    // Get age
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"age", xpathCtx);
    studentInfo->age = (char*)xmlNodeGetContent(ageNode);
    
    // Get citizenship
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"citizenship", xpathCtx);
    studentInfo->citizenship = (char*)xmlNodeGetContent(citizenshipNode);

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return studentInfo; // Return the populated StudentInfo structure
}