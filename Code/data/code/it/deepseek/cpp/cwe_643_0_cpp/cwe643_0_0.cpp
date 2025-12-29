#include <map>
#include <string>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <memory>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Inizializza la libreria XML
    xmlInitParser();
    
    // Parser del documento XML dalla stringa
    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc(
        xmlReadMemory(xml_data.c_str(), xml_data.size(), nullptr, nullptr, 0),
        xmlFreeDoc
    );
    
    if (!doc) {
        xmlCleanupParser();
        return result;
    }
    
    // Crea il contesto XPath
    std::unique_ptr<xmlXPathContext, decltype(&xmlXPathFreeContext)> context(
        xmlXPathNewContext(doc.get()),
        xmlXPathFreeContext
    );
    
    if (!context) {
        xmlCleanupParser();
        return result;
    }
    
    // Costruisci la query XPath per trovare lo studente con username e password specificati
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // Esegui la query XPath
    std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> xpath_result(
        xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context.get()),
        xmlXPathFreeObject
    );
    
    if (!xpath_result || xpath_result->nodesetval == nullptr || xpath_result->nodesetval->nodeNr == 0) {
        xmlCleanupParser();
        return result;
    }
    
    // Prendi il primo nodo studente trovato
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // Estrai le informazioni dallo studente
    for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            
            // Salta username e password poiché non sono richiesti nel risultato
            if (node_name == "username" || node_name == "password") {
                continue;
            }
            
            // Estrai il contenuto del nodo
            xmlChar* content = xmlNodeGetContent(child);
            if (content) {
                result[node_name] = reinterpret_cast<const char*>(content);
                xmlFree(content);
            }
        }
    }
    
    xmlCleanupParser();
    return result;
}