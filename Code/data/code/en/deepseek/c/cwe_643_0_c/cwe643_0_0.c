#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    xmlChar *name = NULL, *age = NULL, *citizenship = NULL;
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
    
    // Get the nodeset result
    nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        goto cleanup;  // No matching student found
    }
    
    // We found a matching student, now extract the information
    xmlNodePtr studentNode = nodes->nodeTab[0];
    xmlNodePtr child = studentNode->children;
    
    // Allocate result structure
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initialize pointers to NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Traverse child nodes to find name, age, and citizenship
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            if (strcmp((char*)child->name, "name") == 0) {
                name = xmlNodeGetContent(child);
                if (name != NULL) {
                    result->name = strdup((char*)name);
                    xmlFree(name);
                }
            } else if (strcmp((char*)child->name, "age") == 0) {
                age = xmlNodeGetContent(child);
                if (age != NULL) {
                    result->age = strdup((char*)age);
                    xmlFree(age);
                }
            } else if (strcmp((char*)child->name, "citizenship") == 0) {
                citizenship = xmlNodeGetContent(child);
                if (citizenship != NULL) {
                    result->citizenship = strdup((char*)citizenship);
                    xmlFree(citizenship);
                }
            }
        }
        child = child->next;
    }
    
    // Check if all required fields were found
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Free partially allocated structure
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Cleanup
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