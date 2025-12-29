#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// Pieni XML-jäsenninkirjasto käsin toteutettuna
class XmlNode {
public:
    std::string tag;
    std::string content;
    std::vector<std::shared_ptr<XmlNode>> children;
    std::map<std::string, std::string> attributes;
    
    XmlNode(const std::string& t = "") : tag(t) {}
    
    std::shared_ptr<XmlNode> findChildByTag(const std::string& tagName) const {
        for (const auto& child : children) {
            if (child->tag == tagName) {
                return child;
            }
        }
        return nullptr;
    }
    
    std::vector<std::shared_ptr<XmlNode>> findChildrenByTag(const std::string& tagName) const {
        std::vector<std::shared_ptr<XmlNode>> result;
        for (const auto& child : children) {
            if (child->tag == tagName) {
                result.push_back(child);
            }
        }
        return result;
    }
};

class XmlParser {
private:
    std::string xml;
    size_t pos;
    
    void skipWhitespace() {
        while (pos < xml.size() && std::isspace(xml[pos])) {
            pos++;
        }
    }
    
    std::string readUntil(char delimiter) {
        std::string result;
        while (pos < xml.size() && xml[pos] != delimiter) {
            result += xml[pos];
            pos++;
        }
        return result;
    }
    
    std::string readTagName() {
        std::string name;
        while (pos < xml.size() && !std::isspace(xml[pos]) && xml[pos] != '>' && xml[pos] != '/') {
            name += xml[pos];
            pos++;
        }
        return name;
    }
    
    std::shared_ptr<XmlNode> parseNode() {
        skipWhitespace();
        
        if (pos >= xml.size() || xml[pos] != '<') {
            return nullptr;
        }
        
        pos++; // Skip '<'
        
        // Check for closing tag
        if (xml[pos] == '/') {
            return nullptr;
        }
        
        auto node = std::make_shared<XmlNode>();
        node->tag = readTagName();
        
        // Skip attributes for simplicity
        while (pos < xml.size() && xml[pos] != '>') {
            pos++;
        }
        
        if (pos >= xml.size()) {
            return nullptr;
        }
        
        pos++; // Skip '>'
        
        // Parse content and children
        while (pos < xml.size()) {
            skipWhitespace();
            
            if (pos >= xml.size()) {
                break;
            }
            
            if (xml[pos] == '<') {
                if (pos + 1 < xml.size() && xml[pos + 1] == '/') {
                    // Closing tag
                    while (pos < xml.size() && xml[pos] != '>') {
                        pos++;
                    }
                    if (pos < xml.size()) {
                        pos++; // Skip '>'
                    }
                    break;
                } else {
                    // Child node
                    auto child = parseNode();
                    if (child) {
                        node->children.push_back(child);
                    }
                }
            } else {
                // Content
                size_t start = pos;
                while (pos < xml.size() && xml[pos] != '<') {
                    pos++;
                }
                node->content = xml.substr(start, pos - start);
                
                // Trim whitespace
                node->content.erase(0, node->content.find_first_not_of(" \t\n\r"));
                node->content.erase(node->content.find_last_not_of(" \t\n\r") + 1);
            }
        }
        
        return node;
    }
    
public:
    XmlParser(const std::string& xmlStr) : xml(xmlStr), pos(0) {}
    
    std::shared_ptr<XmlNode> parse() {
        skipWhitespace();
        return parseNode();
    }
};

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Jäsennä XML
    XmlParser parser(xml_data);
    auto root = parser.parse();
    
    if (!root || root->tag != "students") {
        return result;
    }
    
    // Etsi kaikki opiskelijat
    auto studentNodes = root->findChildrenByTag("student");
    
    for (const auto& studentNode : studentNodes) {
        // Tarkista käyttäjänimi
        auto usernameNode = studentNode->findChildByTag("username");
        if (!usernameNode || usernameNode->content != username) {
            continue;
        }
        
        // Tarkista salasana
        auto passwordNode = studentNode->findChildByTag("password");
        if (!passwordNode || passwordNode->content != password) {
            continue;
        }
        
        // Jos löytyi, kerää tiedot
        auto nameNode = studentNode->findChildByTag("name");
        auto citizenshipNode = studentNode->findChildByTag("citizenship");
        auto ageNode = studentNode->findChildByTag("age");
        
        if (nameNode) {
            result["name"] = nameNode->content;
        }
        
        if (citizenshipNode) {
            result["citizenship"] = citizenshipNode->content;
        }
        
        if (ageNode) {
            result["age"] = ageNode->content;
        }
        
        // Löytyi, palauta tulos
        return result;
    }
    
    // Ei löytynyt
    return result;
}