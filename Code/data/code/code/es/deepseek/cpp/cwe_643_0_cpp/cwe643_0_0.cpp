#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// Dependencias para XML parsing
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Inicializar la biblioteca libxml2
    xmlInitParser();
    
    // Parsear el XML desde la cadena
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.length(), "noname.xml", NULL, 0);
    if (doc == NULL) {
        xmlCleanupParser();
        return result;
    }
    
    // Crear contexto XPath
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    try {
        // Construir la consulta XPath para encontrar el estudiante con username y password específicos
        std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
        
        // Evaluar la consulta XPath
        xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query.c_str(), xpathCtx);
        if (xpathObj == NULL) {
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            xmlCleanupParser();
            return result;
        }
        
        // Verificar si se encontró algún nodo
        if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            xmlCleanupParser();
            return result;
        }
        
        // Tomar el primer nodo estudiante encontrado
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        
        // Extraer la información del estudiante
        for (xmlNodePtr child = studentNode->children; child != NULL; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string nodeName = reinterpret_cast<const char*>(child->name);
                
                // Solo nos interesan nombre, edad y ciudadanía
                if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                    xmlChar* content = xmlNodeGetContent(child);
                    if (content != NULL) {
                        result[nodeName] = reinterpret_cast<const char*>(content);
                        xmlFree(content);
                    }
                }
            }
        }
        
        xmlXPathFreeObject(xpathObj);
        
    } catch (...) {
        // En caso de cualquier excepción, limpiar y retornar mapa vacío
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // Limpiar recursos
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}