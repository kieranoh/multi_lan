#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analiza los datos XML y devuelve la información del estudiante para el nombre de usuario y la contraseña dados. Los datos XML tendrán la siguiente estructura:
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

Podemos construir una consulta XPath y usarla para buscar.

@param xml_data Los datos XML que contienen la información del estudiante.
@param username El nombre de usuario del estudiante a buscar.
@param password La contraseña del estudiante a buscar.

@return Un puntero a una estructura StudentInfo si se encuentra al estudiante. De lo contrario, devuelve NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Inicializar la biblioteca libxml2
    xmlInitParser();
    
    // Parsear el XML desde la cadena
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Crear contexto XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Construir la consulta XPath para encontrar el estudiante con username y password específicos
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Evaluar la consulta XPath
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Verificar si se encontró algún resultado
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Tomar el primer nodo estudiante que coincide
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Crear la estructura de resultado
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicializar los campos a NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Recorrer los hijos del nodo estudiante para extraer la información
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
    
    // Verificar que todos los campos necesarios se extrajeron correctamente
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Liberar memoria si falta algún campo
        free(result->name);
        free(result->age);
        free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Liberar recursos
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Limpiar la biblioteca libxml2
    xmlCleanupParser();
    
    return result;
}