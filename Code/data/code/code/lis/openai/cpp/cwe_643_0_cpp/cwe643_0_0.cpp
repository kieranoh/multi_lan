#include <iostream>
#include <string>
#include <map>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    // Parse the XML data
    xmlDocPtr doc = xmlParseMemory(xml_data.c_str(), xml_data.size());
    if (doc == nullptr) {
        return student_info; // Return empty map if parsing fails
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        xmlFreeDoc(doc);
        return student_info; // Return empty map if context creation fails
    }

    // Construct XPath query to find the student with the given username and password
    std::string xpathQuery = "/students/student[username='" + username + "' and password='" + password + "']";
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpathQuery.c_str()), xpathCtx);

    if (xpathObj != nullptr && xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

        // Extract student information
        for (xmlNodePtr child = studentNode->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                std::string nodeName(reinterpret_cast<const char*>(child->name));
                std::string nodeContent(reinterpret_cast<const char*>(xmlNodeGetContent(child)));

                // Store relevant information in the map
                if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                    student_info[nodeName] = nodeContent;
                }
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the map containing student info
}