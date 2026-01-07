#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// XML 파싱을 위한 간단한 헬퍼 클래스
class SimpleXMLParser {
public:
    struct Node {
        std::string tag;
        std::string content;
        std::vector<std::shared_ptr<Node>> children;
        std::shared_ptr<Node> parent;
        
        std::shared_ptr<Node> findChild(const std::string& tagName) const {
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
        
        std::vector<std::shared_ptr<Node>> stack;
        stack.push_back(root);
        
        size_t pos = 0;
        while (pos < xml.length()) {
            // 태그 시작 찾기
            size_t tagStart = xml.find('<', pos);
            if (tagStart == std::string::npos) break;
            
            // 태그 종료 찾기
            size_t tagEnd = xml.find('>', tagStart);
            if (tagEnd == std::string::npos) break;
            
            std::string tag = xml.substr(tagStart + 1, tagEnd - tagStart - 1);
            
            // 닫는 태그인지 확인
            if (tag[0] == '/') {
                if (!stack.empty()) {
                    stack.pop_back();
                }
                pos = tagEnd + 1;
                continue;
            }
            
            // 새로운 노드 생성
            auto newNode = std::make_shared<Node>();
            newNode->tag = tag;
            newNode->parent = stack.back();
            
            // 내용 찾기
            size_t contentStart = tagEnd + 1;
            size_t nextTagStart = xml.find('<', contentStart);
            
            if (nextTagStart != std::string::npos) {
                std::string content = xml.substr(contentStart, nextTagStart - contentStart);
                // 공백 제거
                size_t firstNonSpace = content.find_first_not_of(" \t\n\r");
                size_t lastNonSpace = content.find_last_not_of(" \t\n\r");
                
                if (firstNonSpace != std::string::npos) {
                    newNode->content = content.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
                }
                
                // 스택에 추가
                stack.back()->children.push_back(newNode);
                
                // 다음 태그가 닫는 태그가 아니면 스택에 push
                if (nextTagStart < xml.length() - 1 && xml[nextTagStart + 1] != '/') {
                    stack.push_back(newNode);
                }
                
                pos = nextTagStart;
            } else {
                pos = tagEnd + 1;
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
        // XML 파싱
        auto root = SimpleXMLParser::parse(xml_data);
        
        // students 노드 찾기
        auto studentsNode = root->findChild("students");
        if (!studentsNode) {
            return result;
        }
        
        // 모든 student 노드 순회
        for (const auto& studentNode : studentsNode->children) {
            if (studentNode->tag != "student") continue;
            
            // username 확인
            auto usernameNode = studentNode->findChild("username");
            if (!usernameNode || usernameNode->content != username) {
                continue;
            }
            
            // password 확인
            auto passwordNode = studentNode->findChild("password");
            if (!passwordNode || passwordNode->content != password) {
                continue;
            }
            
            // 모든 정보 수집
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
            
            // 찾았으므로 종료
            break;
        }
        
    } catch (const std::exception& e) {
        // 파싱 오류 발생 시 빈 맵 반환
        return std::map<std::string, std::string>();
    }
    
    return result;
}