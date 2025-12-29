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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    // Parse XML from memory
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        return NULL;
    }
    
    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Construct XPath query to find student with matching username and password
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // No matching student found
        if (xpathObj != NULL) {
            xmlXPathFreeObject(xpathObj);
        }
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Get the matching student node
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Allocate memory for result
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Initialize fields to NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Extract child nodes
    xmlNodePtr child = studentNode->children;
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
                if (strcmp((char*)child->name, "name") == 0) {
                    result->name = strdup((char*)content);
                } else if (strcmp((char*)child->name, "age") == 0) {
                    result->age = strdup((char*)content);
                } else if (strcmp((char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup((char*)content);
                }
                xmlFree(content);
            }
        }
        child = child->next;
    }
    
    // Check if all required fields were found
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Cleanup if any field is missing
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return result;
}