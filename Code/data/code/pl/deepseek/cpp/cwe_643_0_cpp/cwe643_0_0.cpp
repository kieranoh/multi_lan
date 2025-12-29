#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// Deklaracja klasy parsera XML
class XMLParser {
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
        skipWhitespace();
        if (pos >= xml.size() || xml[pos] != '<') {
            return "";
        }
        pos++; // Skip '<'
        
        // Skip optional '/' for closing tags
        if (pos < xml.size() && xml[pos] == '/') {
            pos++;
        }
        
        std::string tagName = readUntil('>');
        // Remove any attributes
        size_t spacePos = tagName.find(' ');
        if (spacePos != std::string::npos) {
            tagName = tagName.substr(0, spacePos);
        }
        return tagName;
    }
    
    std::string readTextContent() {
        std::string content;
        while (pos < xml.size() && xml[pos] != '<') {
            content += xml[pos];
            pos++;
        }
        // Trim whitespace
        size_t start = 0;
        while (start < content.size() && std::isspace(content[start])) {
            start++;
        }
        size_t end = content.size();
        while (end > start && std::isspace(content[end - 1])) {
            end--;
        }
        return content.substr(start, end - start);
    }
    
public:
    XMLParser(const std::string& xml_str) : xml(xml_str), pos(0) {}
    
    struct XMLNode {
        std::string tag;
        std::string text;
        std::vector<std::unique_ptr<XMLNode>> children;
        std::map<std::string, std::string> attributes;
        
        XMLNode* getFirstChild(const std::string& tag_name) {
            for (auto& child : children) {
                if (child->tag == tag_name) {
                    return child.get();
                }
            }
            return nullptr;
        }
        
        std::vector<XMLNode*> getChildren(const std::string& tag_name) {
            std::vector<XMLNode*> result;
            for (auto& child : children) {
                if (child->tag == tag_name) {
                    result.push_back(child.get());
                }
            }
            return result;
        }
        
        std::string getText() const {
            return text;
        }
    };
    
    std::unique_ptr<XMLNode> parse() {
        skipWhitespace();
        if (pos >= xml.size() || xml[pos] != '<') {
            return nullptr;
        }
        
        auto root = std::make_unique<XMLNode>();
        root->tag = readTagName();
        
        parseNode(root.get());
        return root;
    }
    
private:
    void parseNode(XMLNode* node) {
        while (pos < xml.size()) {
            skipWhitespace();
            
            if (pos >= xml.size()) {
                break;
            }
            
            // Check for closing tag
            if (xml[pos] == '<' && pos + 1 < xml.size() && xml[pos + 1] == '/') {
                // Skip to '>'
                while (pos < xml.size() && xml[pos] != '>') {
                    pos++;
                }
                if (pos < xml.size()) {
                    pos++; // Skip '>'
                }
                break;
            }
            
            // Check for new child node
            if (xml[pos] == '<') {
                auto child = std::make_unique<XMLNode>();
                child->tag = readTagName();
                parseNode(child.get());
                node->children.push_back(std::move(child));
            } else {
                // Read text content
                node->text = readTextContent();
            }
        }
    }
};

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Parse XML
    XMLParser parser(xml_data);
    auto root = parser.parse();
    
    if (!root) {
        return result;
    }
    
    // Find all student nodes
    auto students = root->getChildren("student");
    
    for (auto* student : students) {
        // Get username and password
        auto* username_node = student->getFirstChild("username");
        auto* password_node = student->getFirstChild("password");
        
        if (!username_node || !password_node) {
            continue;
        }
        
        std::string found_username = username_node->getText();
        std::string found_password = password_node->getText();
        
        // Check if this is the student we're looking for
        if (found_username == username && found_password == password) {
            // Get name
            auto* name_node = student->getFirstChild("name");
            if (name_node) {
                result["name"] = name_node->getText();
            }
            
            // Get citizenship
            auto* citizenship_node = student->getFirstChild("citizenship");
            if (citizenship_node) {
                result["citizenship"] = citizenship_node->getText();
            }
            
            // Get age
            auto* age_node = student->getFirstChild("age");
            if (age_node) {
                result["age"] = age_node->getText();
            }
            
            // Found the student, no need to continue searching
            break;
        }
    }
    
    return result;
}