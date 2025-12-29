#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analizza i dati XML e restituisci le informazioni dello studente per il nome utente e la password forniti. I dati XML avranno la seguente struttura:
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

@param xml_data I dati XML contenenti le informazioni dello studente.
@param username Il nome utente dello studente da cercare.
@param password La password dello studente da cercare.

@return Un puntatore a una struttura StudentInfo se lo studente viene trovato. Altrimenti, restituisce NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    // Inizializza la libreria libxml
    xmlInitParser();
    
    // Parse dell'XML
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Errore nel parsing
    }
    
    // Crea un contesto XPath
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Errore nella creazione del contesto XPath
    }

    // Costruisci la query XPath
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "//student[username='%s' and password='%s']", username, password);

    // Esegui la query XPath
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Nessun studente trovato
    }

    // Ottieni il nodo dello studente
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // Alloca la struttura StudentInfo
    StudentInfo* studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Errore di allocazione
    }

    // Estrai le informazioni dallo studente
    for (xmlNodePtr node = studentNode->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrEqual(node->name, (const xmlChar *)"name")) {
                studentInfo->name = (char*)xmlNodeGetContent(node);
            } else if (xmlStrEqual(node->name, (const xmlChar *)"age")) {
                studentInfo->age = (char*)xmlNodeGetContent(node);
            } else if (xmlStrEqual(node->name, (const xmlChar *)"citizenship")) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(node);
            }
        }
    }

    // Libera le risorse
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return studentInfo;
}