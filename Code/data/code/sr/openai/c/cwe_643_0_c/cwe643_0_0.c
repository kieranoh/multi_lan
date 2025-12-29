#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Parsirati XML podatke i vratiti informacije o studentu za dati korisničko ime i lozinku. XML podaci će imati sledeću strukturu:
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

Možemo konstruisati XPath upit i koristiti ga za pretragu.

@param xml_data XML podaci koji sadrže informacije o studentu.
@param username Korisničko ime studenta koji se traži.
@param password Lozinka studenta koji se traži.

@return Pokazivač na strukturu StudentInfo ako je student pronađen. U suprotnom, vraća NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDoc *doc = xmlParseMemory(xml_data, strlen(xml_data));
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
             "/students/student[username='%s' and password='%s']", username, password);

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
        for (xmlNodePtr node = studentNode->children; node; node = node->next) {
            if (node->type == XML_ELEMENT_NODE) {
                if (xmlStrcmp(node->name, (const xmlChar *)"name") == 0) {
                    studentInfo->name = (char*)xmlNodeGetContent(node);
                } else if (xmlStrcmp(node->name, (const xmlChar *)"age") == 0) {
                    studentInfo->age = (char*)xmlNodeGetContent(node);
                } else if (xmlStrcmp(node->name, (const xmlChar *)"citizenship") == 0) {
                    studentInfo->citizenship = (char*)xmlNodeGetContent(node);
                }
            }
        }
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo;
}