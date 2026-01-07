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
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // XML dokumentua parseatu
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // XPath testuingurua sortu
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath galdera
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", 
             username, password);

    // XPath irakurri
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Ikaslearen informazioa lortu
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Ikaslearen izena, herrialdea eta adina lortu
    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];
    xmlNodePtr current_node = student_node->children;

    while (current_node) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char*)current_node->name, "name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(current_node);
            } else if (strcmp((char*)current_node->name, "age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(current_node);
            } else if (strcmp((char*)current_node->name, "citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(current_node);
            }
        }
        current_node = current_node->next;
    }

    // Garbitu
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}