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
        return NULL;
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct XPath query to find student information based on username and password
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), "//student[username='%s' and password='%s']", username, password);

    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Check if we found a result
    if (xpathObj->nodesetval->nodeNr > 0) {
        student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
        if (student_info == NULL) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL;
        }

        // Extract information
        xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];
        for (xmlNodePtr current_node = student_node->children; current_node; current_node = current_node->next) {
            if (current_node->type == XML_ELEMENT_NODE) {
                if (xmlStrcmp(current_node->name, (const xmlChar*)"name") == 0) {
                    student_info->name = (char*)xmlNodeGetContent(current_node);
                } else if (xmlStrcmp(current_node->name, (const xmlChar*)"age") == 0) {
                    student_info->age = (char*)xmlNodeGetContent(current_node);
                } else if (xmlStrcmp(current_node->name, (const xmlChar*)"citizenship") == 0) {
                    student_info->citizenship = (char*)xmlNodeGetContent(current_node);
                }
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}