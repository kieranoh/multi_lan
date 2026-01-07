#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// 前向声明XML解析器类
class XMLNode;

// 辅助函数：解析XML字符串并构建节点树
std::unique_ptr<XMLNode> parseXML(const std::string& xml_data);

// XML节点类定义
class XMLNode {
public:
    std::string tag;
    std::string content;
    std::vector<std::unique_ptr<XMLNode>> children;
    std::map<std::string, std::string> attributes;
    
    XMLNode(const std::string& t = "") : tag(t) {}
    
    // 查找具有特定标签的子节点
    std::vector<XMLNode*> findChildren(const std::string& tagName) {
        std::vector<XMLNode*> result;
        for (auto& child : children) {
            if (child->tag == tagName) {
                result.push_back(child.get());
            }
        }
        return result;
    }
    
    // 查找具有特定标签和内容的子节点
    XMLNode* findChildWithContent(const std::string& tagName, const std::string& expectedContent) {
        for (auto& child : children) {
            if (child->tag == tagName && child->content == expectedContent) {
                return child.get();
            }
        }
        return nullptr;
    }
    
    // 获取特定标签子节点的内容
    std::string getChildContent(const std::string& tagName) {
        for (auto& child : children) {
            if (child->tag == tagName) {
                return child->content;
            }
        }
        return "";
    }
};

// XML解析器实现
class XMLParser {
private:
    std::string xml;
    size_t pos;
    
    void skipWhitespace() {
        while (pos < xml.size() && std::isspace(xml[pos])) {
            pos++;
        }
    }
    
    std::string parseTagName() {
        size_t start = pos;
        while (pos < xml.size() && (std::isalnum(xml[pos]) || xml[pos] == '_' || xml[pos] == '-')) {
            pos++;
        }
        return xml.substr(start, pos - start);
    }
    
    std::string parseContent() {
        size_t start = pos;
        while (pos < xml.size() && xml[pos] != '<') {
            pos++;
        }
        std::string content = xml.substr(start, pos - start);
        
        // 修剪空白字符
        size_t first = 0;
        while (first < content.size() && std::isspace(content[first])) first++;
        size_t last = content.size();
        while (last > first && std::isspace(content[last-1])) last--;
        
        return content.substr(first, last - first);
    }
    
    std::unique_ptr<XMLNode> parseNode() {
        skipWhitespace();
        if (pos >= xml.size() || xml[pos] != '<') {
            return nullptr;
        }
        
        pos++; // 跳过 '<'
        if (xml[pos] == '/') {
            return nullptr; // 结束标签
        }
        
        std::string tagName = parseTagName();
        auto node = std::make_unique<XMLNode>(tagName);
        
        skipWhitespace();
        
        // 解析结束标签或子节点
        while (pos < xml.size() && xml[pos] != '>') {
            pos++;
        }
        
        if (pos < xml.size() && xml[pos] == '>') {
            pos++; // 跳过 '>'
        }
        
        // 解析内容
        node->content = parseContent();
        
        // 解析子节点
        while (pos < xml.size()) {
            skipWhitespace();
            if (pos < xml.size() && xml[pos] == '<') {
                if (pos + 1 < xml.size() && xml[pos + 1] == '/') {
                    // 结束标签
                    pos++; // 跳过 '<'
                    while (pos < xml.size() && xml[pos] != '>') pos++;
                    if (pos < xml.size() && xml[pos] == '>') pos++;
                    break;
                } else {
                    auto child = parseNode();
                    if (child) {
                        node->children.push_back(std::move(child));
                    }
                }
            } else {
                pos++;
            }
        }
        
        return node;
    }
    
public:
    XMLParser(const std::string& xml_str) : xml(xml_str), pos(0) {}
    
    std::unique_ptr<XMLNode> parse() {
        auto root = parseNode();
        return root;
    }
};

std::unique_ptr<XMLNode> parseXML(const std::string& xml_data) {
    XMLParser parser(xml_data);
    return parser.parse();
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // 解析XML
    auto root = parseXML(xml_data);
    if (!root || root->tag != "students") {
        return result;
    }
    
    // 查找所有student节点
    auto studentNodes = root->findChildren("student");
    
    for (auto* studentNode : studentNodes) {
        // 检查用户名和密码是否匹配
        std::string studentUsername = studentNode->getChildContent("username");
        std::string studentPassword = studentNode->getChildContent("password");
        
        if (studentUsername == username && studentPassword == password) {
            // 找到匹配的学生，提取信息
            result["name"] = studentNode->getChildContent("name");
            result["age"] = studentNode->getChildContent("age");
            result["citizenship"] = studentNode->getChildContent("citizenship");
            return result;
        }
    }
    
    // 未找到匹配的学生
    return result;
}