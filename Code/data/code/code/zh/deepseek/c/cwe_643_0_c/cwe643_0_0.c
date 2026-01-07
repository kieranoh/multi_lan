#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* 解析 XML 数据并返回给定用户名和密码的学生信息。XML 数据将具有以下结构：
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

我们可以构建一个 XPath 查询并使用它进行搜索。

@param xml_data 包含学生信息的 XML 数据。
@param username 要搜索的学生的用户名。
@param password 要搜索的学生的密码。

@return 如果找到学生，则返回指向 StudentInfo 结构的指针。否则，返回 NULL。 */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    if (xml_data == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    // 初始化 libxml2 库
    xmlInitParser();
    
    // 解析 XML 数据
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        xmlCleanupParser();
        return NULL;
    }
    
    // 创建 XPath 上下文
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // 构建 XPath 查询：查找具有指定用户名和密码的学生节点
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // 执行 XPath 查询
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // 获取匹配的节点
    nodes = xpathObj->nodesetval;
    
    // 分配结果结构
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // 初始化结构成员
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // 获取第一个匹配的学生节点
    xmlNodePtr studentNode = nodes->nodeTab[0];
    xmlNodePtr child = studentNode->children;
    
    // 遍历学生节点的子节点，提取信息
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
                if (strcmp((char*)child->name, "name") == 0) {
                    result->name = strdup((char*)content);
                } else if (strcmp((char*)child->name, "age") == 0) {
                    result->age = strdup((char*)content);
                } else if (strcmp((char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup((char*)content);
                }
                xmlFree(content);
            }
        }
        child = child->next;
    }
    
    // 检查是否成功提取了所有必需的信息
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // 如果任何信息缺失，清理并返回 NULL
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // 清理资源
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}