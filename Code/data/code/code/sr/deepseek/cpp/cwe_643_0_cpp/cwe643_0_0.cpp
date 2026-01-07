#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>

// Parser za jednostavan XML - ne koristimo spoljne biblioteke
class SimpleXMLParser {
public:
    struct XMLNode {
        std::string tag;
        std::string content;
        std::vector<std::shared_ptr<XMLNode>> children;
        std::shared_ptr<XMLNode> parent;
        
        std::shared_ptr<XMLNode> findChild(const std::string& tagName) const {
            for (const auto& child : children) {
                if (child->tag == tagName) {
                    return child;
                }
            }
            return nullptr;
        }
        
        std::vector<std::shared_ptr<XMLNode>> findChildren(const std::string& tagName) const {
            std::vector<std::shared_ptr<XMLNode>> result;
            for (const auto& child : children) {
                if (child->tag == tagName) {
                    result.push_back(child);
                }
            }
            return result;
        }
    };

    static std::shared_ptr<XMLNode> parse(const std::string& xml) {
        size_t pos = 0;
        return parseNode(xml, pos, nullptr);
    }

private:
    static std::string readTag(const std::string& xml, size_t& pos) {
        skipWhitespace(xml, pos);
        
        if (pos >= xml.length() || xml[pos] != '<') {
            return "";
        }
        
        pos++; // Skip '<'
        size_t start = pos;
        
        while (pos < xml.length() && xml[pos] != '>' && !isspace(xml[pos])) {
            pos++;
        }
        
        return xml.substr(start, pos - start);
    }
    
    static void skipWhitespace(const std::string& xml, size_t& pos) {
        while (pos < xml.length() && isspace(xml[pos])) {
            pos++;
        }
    }
    
    static std::shared_ptr<XMLNode> parseNode(const std::string& xml, size_t& pos, std::shared_ptr<XMLNode> parent) {
        skipWhitespace(xml, pos);
        
        if (pos >= xml.length() || xml[pos] != '<') {
            return nullptr;
        }
        
        auto node = std::make_shared<XMLNode>();
        node->parent = parent;
        
        // Read opening tag
        pos++; // Skip '<'
        size_t tagStart = pos;
        
        while (pos < xml.length() && xml[pos] != '>') {
            pos++;
        }
        
        if (pos >= xml.length()) {
            throw std::runtime_error("Unclosed tag");
        }
        
        std::string tagWithAttrs = xml.substr(tagStart, pos - tagStart);
        size_t spacePos = tagWithAttrs.find(' ');
        if (spacePos != std::string::npos) {
            node->tag = tagWithAttrs.substr(0, spacePos);
        } else {
            node->tag = tagWithAttrs;
        }
        
        pos++; // Skip '>'
        
        // Read content and children
        while (pos < xml.length()) {
            skipWhitespace(xml, pos);
            
            if (pos >= xml.length()) {
                break;
            }
            
            if (xml[pos] == '<') {
                if (pos + 1 < xml.length() && xml[pos + 1] == '/') {
                    // Closing tag
                    pos += 2; // Skip '</'
                    size_t closeStart = pos;
                    
                    while (pos < xml.length() && xml[pos] != '>') {
                        pos++;
                    }
                    
                    if (pos >= xml.length()) {
                        throw std::runtime_error("Unclosed closing tag");
                    }
                    
                    std::string closeTag = xml.substr(closeStart, pos - closeStart);
                    if (closeTag != node->tag) {
                        throw std::runtime_error("Mismatched tags: " + node->tag + " vs " + closeTag);
                    }
                    
                    pos++; // Skip '>'
                    return node;
                } else {
                    // Child node
                    auto child = parseNode(xml, pos, node);
                    if (child) {
                        node->children.push_back(child);
                    }
                }
            } else {
                // Text content
                size_t contentStart = pos;
                while (pos < xml.length() && xml[pos] != '<') {
                    pos++;
                }
                
                std::string content = xml.substr(contentStart, pos - contentStart);
                // Trim whitespace
                size_t first = content.find_first_not_of(" \t\n\r");
                size_t last = content.find_last_not_of(" \t\n\r");
                
                if (first != std::string::npos && last != std::string::npos) {
                    node->content = content.substr(first, last - first + 1);
                } else {
                    node->content = "";
                }
            }
        }
        
        return node;
    }
};

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    try {
        // Parse XML
        auto root = SimpleXMLParser::parse(xml_data);
        
        if (!root || root->tag != "students") {
            return result;
        }
        
        // Find all student nodes
        auto studentNodes = root->findChildren("student");
        
        for (const auto& studentNode : studentNodes) {
            // Get username and password
            auto usernameNode = studentNode->findChild("username");
            auto passwordNode = studentNode->findChild("password");
            
            if (!usernameNode || !passwordNode) {
                continue;
            }
            
            // Check if credentials match
            if (usernameNode->content == username && passwordNode->content == password) {
                // Get other information
                auto nameNode = studentNode->findChild("name");
                auto citizenshipNode = studentNode->findChild("citizenship");
                auto ageNode = studentNode->findChild("age");
                
                if (nameNode) {
                    result["name"] = nameNode->content;
                }
                
                if (citizenshipNode) {
                    result["citizenship"] = citizenshipNode->content;
                }
                
                if (ageNode) {
                    result["age"] = ageNode->content;
                }
                
                // Also include username and password in the result if needed
                result["username"] = usernameNode->content;
                result["password"] = passwordNode->content;
                
                return result;
            }
        }
    } catch (const std::exception& e) {
        // In case of parsing error, return empty map
        std::cerr << "XML parsing error: " << e.what() << std::endl;
        return result;
    }
    
    return result;
}