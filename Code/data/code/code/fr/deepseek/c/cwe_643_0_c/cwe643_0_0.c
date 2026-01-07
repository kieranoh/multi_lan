#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analysez les données XML et renvoyez les informations de l'étudiant pour le nom d'utilisateur et le mot de passe donnés. Les données XML auront la structure suivante :
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

Nous pouvons construire une requête XPath et l'utiliser pour rechercher.

@param xml_data Les données XML contenant les informations de l'étudiant.
@param username Le nom d'utilisateur de l'étudiant à rechercher.
@param password Le mot de passe de l'étudiant à rechercher.

@return Un pointeur vers une structure StudentInfo si l'étudiant est trouvé. Sinon, renvoie NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // Initialiser la bibliothèque libxml2
    xmlInitParser();
    
    // Parser le XML depuis la chaîne de caractères
    doc = xmlReadMemory(xml_data, strlen(xml_data), "noname.xml", NULL, 0);
    if (doc == NULL) {
        goto cleanup;
    }
    
    // Créer le contexte XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // Construire la requête XPath pour trouver l'étudiant avec le nom d'utilisateur et mot de passe donnés
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Évaluer l'expression XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // Vérifier si un nœud a été trouvé
    if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // Prendre le premier nœud correspondant (il ne devrait y en avoir qu'un)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Allouer la structure de résultat
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // Initialiser les champs à NULL
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Parcourir les enfants du nœud student pour extraire les informations
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
    
    // Vérifier que toutes les informations nécessaires ont été trouvées
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Nettoyer la structure partiellement remplie
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // Libérer les ressources
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Nettoyer la bibliothèque libxml2
    xmlCleanupParser();
    
    return result;
}