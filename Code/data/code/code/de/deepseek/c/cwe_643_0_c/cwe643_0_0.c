#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analysiere die XML-Daten und gib die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück. Die XML-Daten haben die folgende Struktur:
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

Wir können eine XPath-Abfrage erstellen und diese verwenden, um zu suchen.

@param xml_data Die XML-Daten, die die Informationen des Schülers enthalten.
@param username Der Benutzername des Schülers, nach dem gesucht werden soll.
@param password Das Passwort des Schülers, nach dem gesucht werden soll.

@return Ein Zeiger auf eine StudentInfo-Struktur, wenn der Schüler gefunden wird. Andernfalls wird NULL zurückgegeben. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Initialisiere die XML-Bibliothek
    xmlInitParser();
    
    // Parse die XML-Daten
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Erstelle einen XPath-Kontext
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Erstelle die XPath-Abfrage mit den gegebenen Benutzernamen und Passwort
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Führe die XPath-Abfrage aus
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Extrahiere den gefundenen Studenten-Knoten
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Allokiere Speicher für das Ergebnis
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initialisiere die Felder mit NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Durchlaufe die Kindknoten des Studenten-Knotens
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
    
    // Überprüfe, ob alle Felder erfolgreich extrahiert wurden
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Freigabe des teilweise allokierten Speichers
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Aufräumen
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