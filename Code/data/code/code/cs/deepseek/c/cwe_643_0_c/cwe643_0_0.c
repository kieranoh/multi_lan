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
    if (!xml_data || !username || !password) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Inicializace knihovny libxml2
    xmlInitParser();
    
    // Parse XML z řetězce
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Vytvoření XPath kontextu
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Sestavení XPath dotazu pro nalezení studenta s daným uživatelským jménem a heslem
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Spuštění XPath dotazu
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Získání nalezeného uzlu studenta
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Alokace paměti pro výsledek
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicializace členů struktury
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Procházení poduzlů studenta a získání potřebných informací
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
    
    // Kontrola, zda byly získány všechny potřebné informace
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Uvolnění paměti v případě neúplných dat
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Uvolnění prostředků
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