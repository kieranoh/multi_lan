#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Jäsennä XML-tiedot ja palauta opiskelijatiedot annetulle käyttäjänimelle ja salasanalle. XML-tiedoilla on seuraava rakenne:
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

Voimme rakentaa XPath-kyselyn ja käyttää sitä hakemiseen.

@param xml_data Opiskelijatietoja sisältävä XML-data.
@param username Haettavan opiskelijan käyttäjänimi.
@param password Haettavan opiskelijan salasana.

@return Osoitin StudentInfo-rakenteeseen, jos opiskelija löytyy. Muuten palauttaa NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    if (!xml_data || !username || !password) {
        return NULL;
    }
    
    // Alusta XML-kirjasto
    xmlInitParser();
    
    // Jäsennä XML-data muistista
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        xmlCleanupParser();
        return NULL;
    }
    
    // Luo XPath-konteksti
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Rakenna XPath-kysely, joka etsii opiskelijan käyttäjänimen ja salasanan perusteella
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Suorita XPath-kysely
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // Opiskelijaa ei löytynyt
        if (xpathObj) xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Otetaan ensimmäinen vastaava opiskelija (pitäisi olla vain yksi)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Varaa muisti tulokselle
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Alusta kentät
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Käy läpi opiskelijan lapsisolmut
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
    
    // Tarkista, että kaikki tarvittavat kentät löytyivät
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Jos jotain kenttää puuttuu, vapauta muisti ja palauta NULL
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // Siivoa
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}