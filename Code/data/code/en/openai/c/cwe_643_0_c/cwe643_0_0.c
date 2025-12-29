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

/**
Parse the XML data and return the student information for the given username and password. The XML data will have the following structure:
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

We can construct a XPath query and use it to search.

@param xml_data The XML data containing the student information.
@param username The username of the student to search for.
@param password The password of the student to search for.

@return A pointer to a StudentInfo structure if the student is found. Otherwise, returns NULL.
*/
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL; // Failed to parse the XML
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Failed to create XPath context
    }

    // Construct the XPath expression to find the student with the given username and password
    char xpath_expression[256];
    snprintf(xpath_expression, sizeof(xpath_expression), 
             "//student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_expression, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Student not found
    }

    // Allocate memory for StudentInfo
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failed
    }

    // Extract the student information
    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];

    student_info->name = (char*)xmlNodeGetContent(xmlFindNode(student_node->children, BAD_CAST "name"));
    student_info->citizenship = (char*)xmlNodeGetContent(xmlFindNode(student_node->children, BAD_CAST "citizenship"));
    student_info->age = (char*)xmlNodeGetContent(xmlFindNode(student_node->children, BAD_CAST "age"));

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the StudentInfo structure
}