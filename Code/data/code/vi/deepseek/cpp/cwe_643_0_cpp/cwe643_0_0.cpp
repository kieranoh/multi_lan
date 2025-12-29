#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>

// Tiền khai báo cho lớp phân tích XML đơn giản
class SimpleXMLParser {
public:
    struct Node {
        std::string tag;
        std::string content;
        std::vector<std::shared_ptr<Node>> children;
        std::shared_ptr<Node> parent;
        
        std::shared_ptr<Node> findChildByTag(const std::string& tagName) const {
            for (const auto& child : children) {
                if (child->tag == tagName) {
                    return child;
                }
            }
            return nullptr;
        }
    };

    static std::shared_ptr<Node> parse(const std::string& xml) {
        auto root = std::make_shared<Node>();
        root->tag = "root";
        
        std::vector<std::shared_ptr<Node>> nodeStack;
        nodeStack.push_back(root);
        
        size_t pos = 0;
        while (pos < xml.length()) {
            // Bỏ qua khoảng trắng
            while (pos < xml.length() && std::isspace(xml[pos])) {
                pos++;
            }
            
            if (pos >= xml.length()) break;
            
            // Tìm thẻ mở
            if (xml[pos] == '<') {
                size_t endPos = xml.find('>', pos);
                if (endPos == std::string::npos) {
                    throw std::runtime_error("Invalid XML: unclosed tag");
                }
                
                std::string tag = xml.substr(pos + 1, endPos - pos - 1);
                
                // Kiểm tra thẻ đóng
                if (tag[0] == '/') {
                    // Thẻ đóng
                    if (nodeStack.size() > 1) {
                        nodeStack.pop_back();
                    }
                    pos = endPos + 1;
                } else {
                    // Thẻ mở
                    auto newNode = std::make_shared<Node>();
                    newNode->tag = tag;
                    newNode->parent = nodeStack.back();
                    
                    nodeStack.back()->children.push_back(newNode);
                    nodeStack.push_back(newNode);
                    
                    pos = endPos + 1;
                    
                    // Tìm nội dung và thẻ đóng tương ứng
                    size_t closeTagPos = xml.find("</" + tag + ">", pos);
                    if (closeTagPos == std::string::npos) {
                        throw std::runtime_error("Invalid XML: no closing tag for " + tag);
                    }
                    
                    // Trích xuất nội dung
                    newNode->content = xml.substr(pos, closeTagPos - pos);
                    
                    // Loại bỏ khoảng trắng thừa
                    size_t firstNonSpace = newNode->content.find_first_not_of(" \t\n\r");
                    size_t lastNonSpace = newNode->content.find_last_not_of(" \t\n\r");
                    
                    if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
                        newNode->content = newNode->content.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
                    }
                    
                    pos = closeTagPos + tag.length() + 3; // "</tag>"
                    
                    // Đóng thẻ hiện tại
                    nodeStack.pop_back();
                }
            } else {
                pos++;
            }
        }
        
        return root;
    }
};

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    try {
        // Phân tích XML
        auto root = SimpleXMLParser::parse(xml_data);
        
        // Tìm nút students
        auto studentsNode = root->findChildByTag("students");
        if (!studentsNode) {
            return result;
        }
        
        // Duyệt qua tất cả các student
        for (const auto& studentNode : studentsNode->children) {
            if (studentNode->tag != "student") {
                continue;
            }
            
            // Tìm username và password
            auto usernameNode = studentNode->findChildByTag("username");
            auto passwordNode = studentNode->findChildByTag("password");
            
            if (!usernameNode || !passwordNode) {
                continue;
            }
            
            // Kiểm tra thông tin đăng nhập
            if (usernameNode->content == username && passwordNode->content == password) {
                // Tìm các thông tin khác
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
                
                // Thêm username và password vào kết quả (tùy chọn)
                result["username"] = usernameNode->content;
                result["password"] = passwordNode->content;
                
                break; // Tìm thấy sinh viên, dừng tìm kiếm
            }
        }
    } catch (const std::exception& e) {
        // Trong trường hợp lỗi phân tích XML, trả về bản đồ rỗng
        std::cerr << "Error parsing XML: " << e.what() << std::endl;
        return std::map<std::string, std::string>();
    }
    
    return result;
}