#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Parsirati XML podatke i vratiti informacije o studentu za zadano korisničko ime i lozinku. XML podaci će imati sljedeću strukturu:
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

Možemo konstruirati XPath upit i koristiti ga za pretraživanje.

@param xml_data XML podaci koji sadrže informacije o studentu.
@param username Korisničko ime studenta kojeg tražimo.
@param password Lozinka studenta kojeg tražimo.

@return Pokazivač na strukturu StudentInfo ako je student pronađen. Inače, vraća NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* studentInfo = NULL;

    // Parse the XML data
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct the XPath query
    char xpathQuery[256];
    snprintf(xpathQuery, sizeof(xpathQuery), 
             "//student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Allocate memory for StudentInfo
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract the student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    xmlNodePtr childNode;

    // Get name
    childNode = studentNode->children;
    while (childNode != NULL) {
        if (xmlStrcmp(childNode->name, (const xmlChar *)"name") == 0) {
            studentInfo->name = (char*)xmlNodeGetContent(childNode);
        } else if (xmlStrcmp(childNode->name, (const xmlChar *)"age") == 0) {
            studentInfo->age = (char*)xmlNodeGetContent(childNode);
        } else if (xmlStrcmp(childNode->name, (const xmlChar *)"citizenship") == 0) {
            studentInfo->citizenship = (char*)xmlNodeGetContent(childNode);
        }
        childNode = childNode->next;
    }

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}