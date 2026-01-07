#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>

// Вспомогательные классы для простого парсинга XML
class XMLNode {
public:
    std::string tag;
    std::string content;
    std::vector<std::shared_ptr<XMLNode>> children;
    std::map<std::string, std::string> attributes;
    
    XMLNode(const std::string& t = "") : tag(t) {}
    
    std::shared_ptr<XMLNode> findChildByTag(const std::string& t) const {
        for (const auto& child : children) {
            if (child->tag == t) {
                return child;
            }
        }
        return nullptr;
    }
    
    std::vector<std::shared_ptr<XMLNode>> findChildrenByTag(const std::string& t) const {
        std::vector<std::shared_ptr<XMLNode>> result;
        for (const auto& child : children) {
            if (child->tag == t) {
                result.push_back(child);
            }
        }
        return result;
    }
};

class XMLParser {
private:
    std::string xml;
    size_t pos;
    
    void skipWhitespace() {
        while (pos < xml.size() && std::isspace(xml[pos])) {
            pos++;
        }
    }
    
    std::string readUntil(char delimiter, bool includeDelimiter = false) {
        size_t start = pos;
        while (pos < xml.size() && xml[pos] != delimiter) {
            pos++;
        }
        std::string result = xml.substr(start, pos - start);
        if (includeDelimiter && pos < xml.size()) {
            result += xml[pos];
            pos++;
        }
        return result;
    }
    
    std::string readTagName() {
        skipWhitespace();
        if (pos >= xml.size() || xml[pos] != '<') {
            return "";
        }
        pos++;
        return readUntil('>', false);
    }
    
    std::shared_ptr<XMLNode> parseNode() {
        skipWhitespace();
        if (pos >= xml.size() || xml[pos] != '<') {
            return nullptr;
        }
        
        pos++;
        if (xml[pos] == '/') {
            return nullptr;
        }
        
        std::string tagName = readUntil('>', false);
        if (tagName.empty()) {
            return nullptr;
        }
        
        auto node = std::make_shared<XMLNode>(tagName);
        
        skipWhitespace();
        
        while (pos < xml.size()) {
            if (xml[pos] == '<') {
                if (pos + 1 < xml.size() && xml[pos + 1] == '/') {
                    std::string closingTag = readUntil('>', false);
                    pos++;
                    break;
                } else {
                    auto child = parseNode();
                    if (child) {
                        node->children.push_back(child);
                    }
                }
            } else {
                std::string content = readUntil('<', false);
                if (!content.empty()) {
                    node->content = content;
                }
            }
            skipWhitespace();
        }
        
        return node;
    }
    
public:
    XMLParser(const std::string& xmlStr) : xml(xmlStr), pos(0) {}
    
    std::shared_ptr<XMLNode> parse() {
        return parseNode();
    }
};

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    try {
        XMLParser parser(xml_data);
        auto root = parser.parse();
        
        if (!root || root->tag != "students") {
            return result;
        }
        
        auto studentNodes = root->findChildrenByTag("student");
        
        for (const auto& student : studentNodes) {
            auto usernameNode = student->findChildByTag("username");
            auto passwordNode = student->findChildByTag("password");
            
            if (usernameNode && passwordNode && 
                usernameNode->content == username && 
                passwordNode->content == password) {
                
                auto nameNode = student->findChildByTag("name");
                auto citizenshipNode = student->findChildByTag("citizenship");
                auto ageNode = student->findChildByTag("age");
                
                if (nameNode) {
                    result["name"] = nameNode->content;
                }
                if (citizenshipNode) {
                    result["citizenship"] = citizenshipNode->content;
                }
                if (ageNode) {
                    result["age"] = ageNode->content;
                }
                
                return result;
            }
        }
    } catch (const std::exception& e) {
        // В случае ошибки парсинга возвращаем пустую карту
        return result;
    }
    
    return result;
}