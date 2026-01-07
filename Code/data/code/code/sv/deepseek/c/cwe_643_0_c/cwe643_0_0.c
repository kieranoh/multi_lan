#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analysera XML-data och returnera studentinformationen för det angivna användarnamnet och lösenordet. XML-datan kommer att ha följande struktur:
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

Vi kan konstruera en XPath-fråga och använda den för att söka.

@param xml_data XML-datan som innehåller studentinformationen.
@param username Användarnamnet för studenten som ska sökas.
@param password Lösenordet för studenten som ska sökas.

@return En pekare till en StudentInfo-struktur om studenten hittas. Annars returneras NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    // Initiera libxml2
    xmlInitParser();
    
    // Läs XML från minnet
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Skapa XPath-kontext
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Registrera namnrymden (om det behövs)
    // xpathCtx->namespaces = ...;
    
    // Bygg XPath-uttryck för att hitta student med matchande användarnamn och lösenord
    char xpath_expr[512];
    snprintf(xpath_expr, sizeof(xpath_expr),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Utför XPath-frågan
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Kontrollera resultatet
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        // Ingen matchande student hittades
        goto cleanup;
    }
    
    // Hämta den första matchande studentnoden
    nodes = xpathObj->nodesetval;
    xmlNodePtr studentNode = nodes->nodeTab[0];
    
    // Allokera minne för resultatet
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initiera fält till NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Gå igenom barnnoder för att hitta name, age och citizenship
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
    
    // Kontrollera att alla fält hittades
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Om något fält saknas, frigör minnet och returnera NULL
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }
    
cleanup:
    // Städa upp
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