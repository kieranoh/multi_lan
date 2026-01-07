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

/* Analysez les données XML et renvoyez les informations de l'étudiant pour le nom d'utilisateur et le mot de passe donnés. Les données XML auront la structure suivante :
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

Nous pouvons construire une requête XPath et l'utiliser pour rechercher.

@param xml_data Les données XML contenant les informations de l'étudiant.
@param username Le nom d'utilisateur de l'étudiant à rechercher.
@param password Le mot de passe de l'étudiant à rechercher.

@return Un pointeur vers une structure StudentInfo si l'étudiant est trouvé. Sinon, renvoie NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    
    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Error parsing the XML
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Error creating XPath context
    }

    // Construct the XPath query
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "//student[username='%s' and password='%s']", username, password);
    
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr, xpathCtx);
    if (xpathObj == NULL || xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // No matching student found
    }

    // Extract student info
    StudentInfo* studentInfo = malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failure
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    xmlNodePtr childNode;

    // Iterate through child nodes
    for (childNode = studentNode->children; childNode; childNode = childNode->next) {
        if (childNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(childNode->name, (const xmlChar *)"name") == 0) {
                studentInfo->name = (char *)xmlNodeGetContent(childNode);
            } else if (xmlStrcmp(childNode->name, (const xmlChar *)"age") == 0) {
                studentInfo->age = (char *)xmlNodeGetContent(childNode);
            } else if (xmlStrcmp(childNode->name, (const xmlChar *)"citizenship") == 0) {
                studentInfo->citizenship = (char *)xmlNodeGetContent(childNode);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; // Return the filled StudentInfo structure
}