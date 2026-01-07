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
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Carregar el document XML
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // error en carregar XML
    }

    // Crear el context XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // error en crear el context XPath
    }

    // Construir la consulta XPath
    char xpath_expr[256];
    snprintf(xpath_expr, sizeof(xpath_expr), 
             "//student[username='%s' and password='%s']", username, password);

    // Realitzar la consulta XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // no s'ha trobat l'estudiant
    }
    
    // Crear la informació de l'estudiant
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // error en reservar memòria
    }

    // Obtenir informació de l'estudiant
    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];
    student_info->name = (char*)xmlNodeGetContent(xmlGetFirstChild(student_node));
    student_info->age = (char*)xmlGetContent(xmlNodeGetNextSibling(xmlNodeGetNextSibling(student_node)));
    student_info->citizenship = (char*)xmlGetContent(xmlNodeGetNextSibling(xmlNodeGetNextSibling(xmlNodeGetNextSibling(student_node))));

    // Netejar
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}