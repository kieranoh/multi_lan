#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Parseer de XML-gegevens en retourneer de studenteninformatie voor de gegeven gebruikersnaam en wachtwoord. De XML-gegevens hebben de volgende structuur:
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

We kunnen een XPath-query opstellen en deze gebruiken om te zoeken.

@param xml_data De XML-gegevens die de studenteninformatie bevatten.
@param username De gebruikersnaam van de student om naar te zoeken.
@param password Het wachtwoord van de student om naar te zoeken.

@return Een pointer naar een StudentInfo-structuur als de student is gevonden. Anders retourneert het NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse de XML-gegevens
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        fprintf(stderr, "Document is niet goed geparsed.\n");
        return NULL;
    }

    // Creëer een nieuwe XPath-context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Kon geen nieuwe XPath-context creëren.\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    // Stel de XPath-query in om de student te vinden op basis van gebruikersnaam en wachtwoord
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query),
             "//student[username='%s' and password='%s']", username, password);

    // Voer de XPath-query uit
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        fprintf(stderr, "Geen student gevonden met de gegeven gebruikersnaam en wachtwoord.\n");
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Allocatie voor StudentInfo
    student_info = malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        fprintf(stderr, "Geheugen kan niet worden toegewezen voor StudentInfo.\n");
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Verkrijg de informatie van de eerste gevonden student
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // Verkrijg de naam
    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (xmlChar*)"name");
    student_info->name = strdup((char*)xmlNodeGetContent(nameNode));

    // Verkrijg de leeftijd
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (xmlChar*)"age");
    student_info->age = strdup((char*)xmlNodeGetContent(ageNode));

    // Verkrijg de nationaliteit
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (xmlChar*)"citizenship");
    student_info->citizenship = strdup((char*)xmlNodeGetContent(citizenshipNode));

    // Opruimen
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}