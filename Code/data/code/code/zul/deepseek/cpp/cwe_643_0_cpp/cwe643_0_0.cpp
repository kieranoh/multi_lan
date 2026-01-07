#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// XML 파싱을 위한 간단한 헬퍼 클래스
class SimpleXMLParser {
public:
    struct Node {
        std::string tag;
        std::string content;
        std::vector<std::shared_ptr<Node>> children;
        std::shared_ptr<Node> parent;
        
        Node(const std::string& t) : tag(t) {}
    };
    
    static std::shared_ptr<Node> parse(const std::string& xml) {
        auto root = std::make_shared<Node>("root");
        auto current = root;
        std::string currentTag;
        std::string currentContent;
        bool inTag = false;
        bool inContent = false;
        
        for (size_t i = 0; i < xml.length(); i++) {
            if (xml[i] == '<') {
                if (i + 1 < xml.length() && xml[i + 1] == '/') {
                    // 닫는 태그
                    inTag = false;
                    inContent = false;
                    
                    // 현재 노드의 content 설정
                    if (current && !currentContent.empty()) {
                        current->content = currentContent;
                        currentContent.clear();
                    }
                    
                    // 부모 노드로 이동
                    if (current && current->parent) {
                        current = current->parent;
                    }
                    
                    // 태그 끝까지 건너뛰기
                    while (i < xml.length() && xml[i] != '>') i++;
                } else {
                    // 여는 태그
                    inTag = true;
                    inContent = false;
                    currentTag.clear();
                    
                    // 태그 이름 읽기
                    i++;
                    while (i < xml.length() && xml[i] != '>' && !std::isspace(xml[i])) {
                        currentTag += xml[i];
                        i++;
                    }
                    
                    // 새 노드 생성
                    auto newNode = std::make_shared<Node>(currentTag);
                    newNode->parent = current;
                    current->children.push_back(newNode);
                    current = newNode;
                    
                    // 태그 끝까지 건너뛰기
                    while (i < xml.length() && xml[i] != '>') i++;
                    
                    inTag = false;
                    inContent = true;
                    currentContent.clear();
                }
            } else if (inContent && xml[i] != '\n' && xml[i] != '\r' && xml[i] != '\t') {
                currentContent += xml[i];
            }
        }
        
        return root;
    }
    
    static std::vector<std::shared_ptr<Node>> findNodesByTag(
        std::shared_ptr<Node> node, 
        const std::string& tag
    ) {
        std::vector<std::shared_ptr<Node>> result;
        
        if (node->tag == tag) {
            result.push_back(node);
        }
        
        for (auto& child : node->children) {
            auto childResults = findNodesByTag(child, tag);
            result.insert(result.end(), childResults.begin(), childResults.end());
        }
        
        return result;
    }
    
    static std::string getChildContent(
        std::shared_ptr<Node> node, 
        const std::string& childTag
    ) {
        for (auto& child : node->children) {
            if (child->tag == childTag) {
                return child->content;
            }
        }
        return "";
    }
};

std::map<std::string, std::string> get_student_info(
    const std::string& xml_data, 
    const std::string& username, 
    const std::string& password
) {
    std::map<std::string, std::string> result;
    
    // XML 파싱
    auto root = SimpleXMLParser::parse(xml_data);
    
    // 모든 student 노드 찾기
    auto studentNodes = SimpleXMLParser::findNodesByTag(root, "student");
    
    // 각 student 노드 검사
    for (auto& student : studentNodes) {
        std::string studentUsername = SimpleXMLParser::getChildContent(student, "username");
        std::string studentPassword = SimpleXMLParser::getChildContent(student, "password");
        
        // 사용자 이름과 비밀번호가 일치하는지 확인
        if (studentUsername == username && studentPassword == password) {
            // 정보 수집
            std::string name = SimpleXMLParser::getChildContent(student, "name");
            std::string citizenship = SimpleXMLParser::getChildContent(student, "citizenship");
            std::string age = SimpleXMLParser::getChildContent(student, "age");
            
            // 결과 맵에 추가
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            // 찾았으므로 종료
            break;
        }
    }
    
    return result;
}

// 사용 예시:
/*
int main() {
    std::string xml_data = R"(
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>John Doe</name>
        <citizenship>USA</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>Bob Smith</name>
        <citizenship>Canada</citizenship>
        <age>22</age>
    </student>
</students>
    )";
    
    auto info1 = get_student_info(xml_data, "john_doe", "jdpassword");
    auto info2 = get_student_info(xml_data, "bob_smith", "bspassword");
    auto info3 = get_student_info(xml_data, "unknown", "password");
    
    return 0;
}
*/