#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/**
 * Parse de XML-gegevens en retourneer de studenteninformatie voor de gegeven gebruikersnaam en wachtwoord.
 * 
 * @param xml_data De XML-gegevens met de studenteninformatie.
 * @param username De gebruikersnaam van de student om naar te zoeken.
 * @param password Het wachtwoord van de student om naar te zoeken.
 * @return Een map met studenteninformatie (naam, leeftijd, nationaliteit) als deze is gevonden, anders een lege map.
 */
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Initialiseer de XML-bibliotheek
    xmlInitParser();
    
    // Parse de XML-gegevens
    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc(
        xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", nullptr, 0),
        xmlFreeDoc
    );
    
    if (!doc) {
        std::cerr << "Fout bij het parsen van XML-gegevens" << std::endl;
        xmlCleanupParser();
        return result;
    }
    
    // Maak een XPath-context
    std::unique_ptr<xmlXPathContext, decltype(&xmlXPathFreeContext)> context(
        xmlXPathNewContext(doc.get()),
        xmlXPathFreeContext
    );
    
    if (!context) {
        std::cerr << "Fout bij het maken van XPath-context" << std::endl;
        xmlCleanupParser();
        return result;
    }
    
    // Registreer de namespace (indien nodig, maar onze XML heeft geen namespace)
    // context->registerNs("ns", BAD_CAST "http://example.com/ns");
    
    // Bouw de XPath-query om de student te vinden met de gegeven gebruikersnaam en wachtwoord
    std::string xpath_query = 
        "/students/student[username/text()='" + username + 
        "' and password/text()='" + password + "']";
    
    // Voer de XPath-query uit
    std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> xpath_result(
        xmlXPathEvalExpression(BAD_CAST xpath_query.c_str(), context.get()),
        xmlXPathFreeObject
    );
    
    if (!xpath_result) {
        std::cerr << "Fout bij het uitvoeren van XPath-query" << std::endl;
        xmlCleanupParser();
        return result;
    }
    
    // Controleer of er een student is gevonden
    if (xpath_result->nodesetval == nullptr || xpath_result->nodesetval->nodeNr == 0) {
        xmlCleanupParser();
        return result; // Geen student gevonden, retourneer lege map
    }
    
    // Neem de eerste gevonden student (er zou er maar één moeten zijn)
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // Functie om de tekstinhoud van een kindknoop op te halen
    auto get_child_text = [](xmlNodePtr parent, const char* child_name) -> std::string {
        for (xmlNodePtr child = parent->children; child != nullptr; child = child->next) {
            if (child->type == XML_ELEMENT_NODE && 
                xmlStrcmp(child->name, BAD_CAST child_name) == 0) {
                xmlChar* content = xmlNodeGetContent(child);
                if (content) {
                    std::string result_str(reinterpret_cast<const char*>(content));
                    xmlFree(content);
                    return result_str;
                }
                break;
            }
        }
        return "";
    };
    
    // Haal de informatie op
    std::string name = get_child_text(student_node, "name");
    std::string age = get_child_text(student_node, "age");
    std::string citizenship = get_child_text(student_node, "citizenship");
    
    // Voeg de informatie toe aan de resultaatmap
    if (!name.empty()) result["name"] = name;
    if (!age.empty()) result["age"] = age;
    if (!citizenship.empty()) result["citizenship"] = citizenship;
    
    // Opruimen
    xmlCleanupParser();
    
    return result;
}