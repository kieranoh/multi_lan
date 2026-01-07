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
    
    // Inizializatu libxml2
    xmlInitParser();
    
    // Parseatu XML datua memoria-bufferretik
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Sortu XPath testuingurua
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Eraiki XPath adierazpena erabiltzaile izena eta pasahitza egiaztatzeko
    char xpath_expr[512];
    snprintf(xpath_expr, sizeof(xpath_expr),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Exekutatu XPath kontsulta
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Egiaztatu emaitza
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        // Ez da ikaslerik aurkitu
        goto cleanup;
    }
    
    // Hartu lehenengo student nodoa (bakarra izan beharko luke)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Sortu emaitza egitura
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Hasieratu eremuak
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Bilatu beharrezko azpieremuak student nodoan
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
    
    // Egiaztatu beharrezko eremu guztiak daudela
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Datuak osorik ez daude, garbitu eta NULL itzuli
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Garbitu libxml2 baliabideak
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