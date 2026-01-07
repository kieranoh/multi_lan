#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Initialiseer de XML-bibliotheek
    xmlInitParser();
    
    // Parse de XML-gegevens uit het geheugen
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Maak een XPath-context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Bouw de XPath-query om de student te vinden met de gegeven gebruikersnaam en wachtwoord
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Evalueer de XPath-query
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Controleer of er een resultaat is
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Neem het eerste gevonden studentknooppunt
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Alloceer geheugen voor het resultaat
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initialiseer de structuurvelden
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Loop door de child-elementen van het studentknooppunt
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
    
    // Controleer of alle vereiste velden zijn gevonden
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Vrijgeven van toegewezen geheugen als er velden ontbreken
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Opruimen van XML-bronnen
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Opruimen van de XML-bibliotheek
    xmlCleanupParser();
    
    return result;
}