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
    xmlDocPtr doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Error al analizar el XML
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Error al crear el contexto XPath
    }

    char xpath_expression[256];
    snprintf(xpath_expression, sizeof(xpath_expression), 
             "//student[username='%s' and password='%s']", username, password);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expression, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Estudiante no encontrado
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    StudentInfo* studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Error al asignar memoria
    }

    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"name", xpathCtx);
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"age", xpathCtx);
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"citizenship", xpathCtx);

    studentInfo->name = (char*)xmlNodeGetContent(nameNode);
    studentInfo->age = (char*)xmlNodeGetContent(ageNode);
    studentInfo->citizenship = (char*)xmlNodeGetContent(citizenshipNode);

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; // Regresa la información del estudiante
}