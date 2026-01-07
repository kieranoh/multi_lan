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

/* Analise os dados XML e retorne as informações do aluno para o nome de usuário e senha fornecidos. Os dados XML terão a seguinte estrutura:
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

@param xml_data Os dados XML contendo as informações do aluno.
@param username O nome de usuário do aluno a ser pesquisado.
@param password A senha do aluno a ser pesquisado.

@return Um ponteiro para uma estrutura StudentInfo se o aluno for encontrado. Caso contrário, retorna NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Inicialização da biblioteca libxml
    xmlInitParser();
    
    // Parse do XML
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Erro ao fazer o parse do XML
    }

    // Criação do contexto XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Erro ao criar contexto XPath
    }

    // Criação da consulta XPath
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']", username, password);

    // Execução da consulta XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Aluno não encontrado
    }

    // Aluno encontrado, alocando memória para StudentInfo
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Erro ao alocar memória
    }

    // Extraindo informações do aluno
    for (int i = 0; i < xpathObj->nodesetval->nodeNr; ++i) {
        xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[i];

        // Extrair nome
        xmlNodePtr name_node = xmlXPathNodeEval(student_node, (const xmlChar*) "name");
        student_info->name = strdup((char*)xmlNodeGetContent(name_node));
        
        // Extrair cidadania
        xmlNodePtr citizenship_node = xmlXPathNodeEval(student_node, (const xmlChar*) "citizenship");
        student_info->citizenship = strdup((char*)xmlNodeGetContent(citizenship_node));
        
        // Extrair idade
        xmlNodePtr age_node = xmlXPathNodeEval(student_node, (const xmlChar*) "age");
        student_info->age = strdup((char*)xmlNodeGetContent(age_node));
    }

    // Limpeza
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return student_info; // Retorna as informações do aluno
}