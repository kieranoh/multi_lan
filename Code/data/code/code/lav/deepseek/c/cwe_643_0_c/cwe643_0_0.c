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
    
    // Initialize libxml2
    xmlInitParser();
    
    // Parse XML from memory
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Build XPath query to find student with matching username and password
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Evaluate XPath expression
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Check if we found a matching student
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Get the first matching student node
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Allocate memory for result
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initialize all fields to NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Traverse child nodes to extract information
    xmlNodePtr child = studentNode->children;
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlNodePtr contentNode = child->children;
            if (contentNode != NULL && contentNode->content != NULL) {
                char* content = (char*)contentNode->content;
                
                if (strcmp((char*)child->name, "name") == 0) {
                    result->name = strdup(content);
                } else if (strcmp((char*)child->name, "age") == 0) {
                    result->age = strdup(content);
                } else if (strcmp((char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup(content);
                }
            }
        }
        child = child->next;
    }
    
    // Check if we successfully extracted all required fields
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Free partially allocated memory
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Cleanup XPath objects
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Cleanup libxml2
    xmlCleanupParser();
    
    return result;
}