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
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    // Inicjalizacja parsera XML
    xmlInitParser();
    
    // Parsowanie danych XML z ciągu znaków
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Tworzenie kontekstu XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Konstruowanie zapytania XPath
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Wykonanie zapytania XPath
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Pobranie zbioru węzłów
    nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        goto cleanup;
    }
    
    // Tworzenie struktury wynikowej
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicjalizacja pól struktury
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Pobieranie danych z węzła studenta
    xmlNodePtr studentNode = nodes->nodeTab[0];
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
    
    // Sprawdzenie, czy wszystkie wymagane pola zostały znalezione
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Zwolnienie zasobów
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