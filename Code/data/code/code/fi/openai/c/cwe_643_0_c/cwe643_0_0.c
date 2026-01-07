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
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Alustetaan libxml2
    xmlInitParser();
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Virheellinen XML
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Virhe kontekstin luomisessa
    }

    // Luo XPath-kysely
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query),
             "//student[username='%s' and password='%s']", username, password);

    // Suorita XPath-kysely
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Virhe XPath-kyselyssä
    }

    // Tarkista, löytyikö opiskelija
    if (xpathObj->nodesetval->nodeNr > 0) {
        student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
        if (student_info == NULL) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL; // Muistin allokointivirhe
        }

        // Hae opiskelijan tiedot
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

        // Hae nimi
        xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"name", xpathCtx);
        student_info->name = (char*)xmlNodeGetContent(nameNode);
        xmlXPathFreeObject(nameNode);

        // Hae kansalaisuus
        xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"citizenship", xpathCtx);
        student_info->citizenship = (char*)xmlNodeGetContent(citizenshipNode);
        xmlXPathFreeObject(citizenshipNode);

        // Hae ikä
        xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar *)"age", xpathCtx);
        student_info->age = (char*)xmlNodeGetContent(ageNode);
        xmlXPathFreeObject(ageNode);
    }

    // Vapauta kaikki
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return student_info;
}