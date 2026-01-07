#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Parsi XML data a vrať informace o studentovi pro zadané uživatelské jméno a heslo. XML data budou mít následující strukturu:
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

Můžeme sestavit XPath dotaz a použít ho k vyhledávání.

@param xml_data XML data obsahující informace o studentech.
@param username Uživatelské jméno studenta, kterého hledáme.
@param password Heslo studenta, kterého hledáme.

@return Ukazatel na strukturu StudentInfo, pokud je student nalezen. Jinak vrací NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    // Načtení XML dat
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    // Vytvoření XPath kontextu
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Sestavení XPath dotazu
    char xpathQuery[256];
    snprintf(xpathQuery, sizeof(xpathQuery), 
             "//student[username='%s' and password='%s']", username, password);

    // Vyhodnocení XPath dotazu
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Získání informací o studentovi
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    StudentInfo* studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extrakce dat
    for (xmlNodePtr currentNode = studentNode->children; currentNode; currentNode = currentNode->next) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            if (strcmp((const char*)currentNode->name, "name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(currentNode);
            } else if (strcmp((const char*)currentNode->name, "age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(currentNode);
            } else if (strcmp((const char*)currentNode->name, "citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(currentNode);
            }
        }
    }

    // Uklidění
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}