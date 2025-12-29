#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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

Podemos construir uma consulta XPath e usá-la para pesquisar.

@param xml_data Os dados XML contendo as informações do aluno.
@param username O nome de usuário do aluno a ser pesquisado.
@param password A senha do aluno a ser pesquisado.

@return Um ponteiro para uma estrutura StudentInfo se o aluno for encontrado. Caso contrário, retorna NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    // Inicializar a biblioteca libxml2
    xmlInitParser();
    
    // Parse o XML da string fornecida
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Criar contexto XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Construir a consulta XPath para encontrar o aluno com username e password específicos
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Executar a consulta XPath
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Verificar se encontramos algum nó
    nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        goto cleanup;  // Aluno não encontrado
    }
    
    // Alocar memória para a estrutura de resultado
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Inicializar os membros da estrutura
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Pegar o primeiro nó correspondente (deve ser apenas um)
    xmlNodePtr studentNode = nodes->nodeTab[0];
    xmlNodePtr child = studentNode->children;
    
    // Percorrer os filhos do nó student para extrair name, age e citizenship
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
    
    // Verificar se todos os campos necessários foram encontrados
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Liberar memória parcialmente alocada
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
    
    xmlCleanupParser();
    
    return result;
}