#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Parsd a XML adatokat, és térj vissza a diák információkkal a megadott felhasználónévvel és jelszóval. A XML adatok a következő struktúrával rendelkeznek:
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

Készíthetünk egy XPath lekérdezést, és használhatjuk a kereséshez.

@param xml_data A XML adat, amely a diák információkat tartalmazza.
@param username A keresett diák felhasználóneve.
@param password A keresett diák jelszava.

@return Egy mutató a StudentInfo struktúrára, ha a diák megtalálható. Ellenkező esetben NULL-t ad vissza. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // Create a new XPath context
    context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Create the XPath expression
    char xpath_expr[256];
    snprintf(xpath_expr, sizeof(xpath_expr), "/students/student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    result = xmlXPathEvalExpression((const xmlChar*)xpath_expr, context);
    if (result == NULL || result->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Allocate memory for the StudentInfo structure
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract the student's information
    xmlNodePtr student_node = result->nodesetval->nodeTab[0];
    for (xmlNodePtr current_node = student_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(current_node->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(current_node);
            } else if (xmlStrcmp(current_node->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(current_node);
            } else if (xmlStrcmp(current_node->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(current_node);
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);

    return student_info;
}