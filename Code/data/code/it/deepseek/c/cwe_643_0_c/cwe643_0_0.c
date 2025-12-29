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

Possiamo costruire una query XPath e usarla per cercare.

@param xml_data I dati XML contenenti le informazioni dello studente.
@param username Il nome utente dello studente da cercare.
@param password La password dello studente da cercare.

@return Un puntatore a una struttura StudentInfo se lo studente viene trovato. Altrimenti, restituisce NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    if (!xml_data || !username || !password) {
        return NULL;
    }

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;

    // Inizializza la libreria libxml2
    xmlInitParser();
    
    // Analizza il documento XML dalla stringa
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }

    // Crea il contesto XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }

    // Costruisci la query XPath per trovare lo studente con username e password specificati
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);

    // Esegui la query XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }

    // Controlla se abbiamo trovato almeno uno studente
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }

    // Prendi il primo nodo studente trovato
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Alloca la struttura risultato
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inizializza i campi a NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;

    // Cerca i figli del nodo studente per estrarre le informazioni
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

    // Verifica che tutti i campi siano stati estratti correttamente
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Se manca qualche campo, libera la memoria e restituisci NULL
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Pulisci le risorse
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Pulisci la libreria libxml2
    xmlCleanupParser();

    return result;
}