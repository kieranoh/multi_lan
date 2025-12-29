#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>

// Dépendances pour le parsing XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Initialiser la bibliothèque libxml2
    xmlInitParser();
    
    // Parser le document XML depuis la chaîne de caractères
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", NULL, 0);
    if (doc == NULL) {
        xmlCleanupParser();
        return result; // Retourner une carte vide en cas d'erreur de parsing
    }
    
    // Créer un contexte XPath
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    try {
        // Construire la requête XPath pour trouver l'étudiant avec le nom d'utilisateur et le mot de passe donnés
        std::string xpath_expr = "/students/student[username='" + username + "' and password='" + password + "']";
        
        // Évaluer l'expression XPath
        xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr.c_str(), xpathCtx);
        if (xpathObj == NULL) {
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            xmlCleanupParser();
            return result;
        }
        
        // Vérifier si des nœuds ont été trouvés
        if (xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            xmlCleanupParser();
            return result; // Aucun étudiant trouvé
        }
        
        // Prendre le premier nœud correspondant (normalement il ne devrait y en avoir qu'un)
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        
        // Parcourir les enfants du nœud student pour extraire les informations
        for (xmlNodePtr child = studentNode->children; child != NULL; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string nodeName = reinterpret_cast<const char*>(child->name);
                
                // Extraire le contenu textuel du nœud
                xmlChar* content = xmlNodeGetContent(child);
                if (content != NULL) {
                    std::string nodeValue = reinterpret_cast<const char*>(content);
                    
                    // Ajouter les informations pertinentes à la carte de résultat
                    if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                        result[nodeName] = nodeValue;
                    }
                    
                    xmlFree(content);
                }
            }
        }
        
        // Libérer les ressources XPath
        xmlXPathFreeObject(xpathObj);
        
    } catch (...) {
        // En cas d'exception, nettoyer et retourner une carte vide
        result.clear();
    }
    
    // Libérer les ressources
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}