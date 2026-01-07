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
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Inicijalizacija XML biblioteke
    xmlInitParser();
    
    // Parsiranje XML podataka iz memorije
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Kreiranje XPath konteksta
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Konstrukcija XPath izraza za pronalaženje studenta s datim korisničkim imenom i lozinkom
    char xpath_expr[512];
    snprintf(xpath_expr, sizeof(xpath_expr),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Evaluacija XPath izraza
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Provjera je li pronađen student
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Uzimanje prvog pronađenog čvora (trebao bi biti samo jedan)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Alokacija strukture za rezultat
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicijalizacija polja na NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Prolazak kroz djecu student čvora
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
    
    // Provjera jesu li sva polja postavljena
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Ako nešto nedostaje, oslobađamo alocirane resurse i vraćamo NULL
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Oslobađanje resursa
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    xmlCleanupParser();
    
    return result;
}