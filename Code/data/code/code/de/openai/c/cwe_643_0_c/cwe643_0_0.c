#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analysiere die XML-Daten und gib die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück. Die XML-Daten haben die folgende Struktur:
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

Wir können eine XPath-Abfrage erstellen und diese verwenden, um zu suchen.

@param xml_data Die XML-Daten, die die Informationen des Schülers enthalten.
@param username Der Benutzername des Schülers, nach dem gesucht werden soll.
@param password Das Passwort des Schülers, nach dem gesucht werden soll.

@return Ein Zeiger auf eine StudentInfo-Struktur, wenn der Schüler gefunden wird. Andernfalls wird NULL zurückgegeben. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), 
             "/students/student[username='%s' and password='%s']", 
             username, password);
    
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    StudentInfo* studentInfo = NULL;
    if (xpathObj->nodesetval->nodeNr > 0) {
        studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
        if (studentInfo == NULL) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL;
        }

        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        xmlNodePtr childNode;

        for (childNode = studentNode->children; childNode; childNode = childNode->next) {
            if (childNode->type == XML_ELEMENT_NODE) {
                if (xmlStrcmp(childNode->name, (const xmlChar *)"name") == 0) {
                    studentInfo->name = (char*)xmlNodeGetContent(childNode);
                } else if (xmlStrcmp(childNode->name, (const xmlChar *)"age") == 0) {
                    studentInfo->age = (char*)xmlNodeGetContent(childNode);
                } else if (xmlStrcmp(childNode->name, (const xmlChar *)"citizenship") == 0) {
                    studentInfo->citizenship = (char*)xmlNodeGetContent(childNode);
                }
            }
        }
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}