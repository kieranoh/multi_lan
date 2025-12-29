#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analitza les dades XML i retorna la informació de l'estudiant per al nom d'usuari i contrasenya donats. Les dades XML tindran l'estructura següent:
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

Podem construir una consulta XPath i utilitzar-la per cercar.

@param xml_data Les dades XML que contenen la informació de l'estudiant.
@param username El nom d'usuari de l'estudiant que es vol cercar.
@param password La contrasenya de l'estudiant que es vol cercar.

@return Un punter a una estructura StudentInfo si s'ha trobat l'estudiant. Altrament, retorna NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Inicialitzar la llibreria libxml2
    xmlInitParser();
    
    // Analitzar el document XML des de la cadena
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Crear el context XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Construir la consulta XPath per trobar l'estudiant amb el nom d'usuari i contrasenya donats
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Executar la consulta XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Comprovar si s'ha trobat algun resultat
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Obtenir el node de l'estudiant
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Crear l'estructura de resultat
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicialitzar els camps a NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Recórrer els fills del node de l'estudiant per obtenir les dades
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
    
    // Comprovar si s'han obtingut totes les dades necessàries
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Alliberar memòria si alguna dada falta
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Alliberar recursos
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Netejar la llibreria libxml2
    xmlCleanupParser();
    
    return result;
}