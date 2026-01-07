#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    // XML dokumentum parse-olása memóriából
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }
    
    // XPath kontextus létrehozása
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // XPath lekérdezés összeállítása a felhasználónév és jelszó alapján
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // XPath kiértékelés
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // Nincs találat
        if (xpathObj != NULL) {
            xmlXPathFreeObject(xpathObj);
        }
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Az első találat (csak egy diáknak kell lennie a megadott felhasználónévvel és jelszóval)
    nodes = xpathObj->nodesetval;
    xmlNodePtr studentNode = nodes->nodeTab[0];
    
    // StudentInfo struktúra létrehozása
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Inicializálás NULL értékekkel
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Gyermek elemek bejárása a diák információkért
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
    
    // Ellenőrizzük, hogy minden mezőt sikerült-e kitölteni
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Ha valamelyik mező hiányzik, felszabadítjuk a memóriát és NULL-t adunk vissza
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // Erőforrások felszabadítása
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return result;
}