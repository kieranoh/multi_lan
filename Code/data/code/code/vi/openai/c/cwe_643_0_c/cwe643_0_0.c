#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Phân tích dữ liệu XML và trả về thông tin sinh viên cho tên người dùng và mật khẩu đã cho. Dữ liệu XML sẽ có cấu trúc sau:
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

Chúng ta có thể xây dựng một truy vấn XPath và sử dụng nó để tìm kiếm.

@param xml_data Dữ liệu XML chứa thông tin sinh viên.
@param username Tên người dùng của sinh viên cần tìm.
@param password Mật khẩu của sinh viên cần tìm.

@return Một con trỏ đến cấu trúc StudentInfo nếu sinh viên được tìm thấy. Ngược lại, trả về NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL; // Error parsing XML
    }
    
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Error creating XPath context
    }

    // Create the XPath query
    char xpathQuery[256];
    snprintf(xpathQuery, sizeof(xpathQuery), "//student[username='%s' and password='%s']", username, password);
    
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathQuery, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Error evaluating XPath expression
    }

    if (xpathObj->nodesetval->nodeNr > 0) {
        student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
        if (student_info == NULL) {
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtx);
            xmlFreeDoc(doc);
            return NULL; // Error allocating memory
        }

        // Extract the student information
        xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
        for (xmlNodePtr currentNode = studentNode->children; currentNode; currentNode = currentNode->next) {
            if (currentNode->type == XML_ELEMENT_NODE) {
                if (strcmp((const char*)currentNode->name, "name") == 0) {
                    student_info->name = (char*)xmlNodeGetContent(currentNode);
                } else if (strcmp((const char*)currentNode->name, "age") == 0) {
                    student_info->age = (char*)xmlNodeGetContent(currentNode);
                } else if (strcmp((const char*)currentNode->name, "citizenship") == 0) {
                    student_info->citizenship = (char*)xmlNodeGetContent(currentNode);
                }
            }
        }
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the found student information or NULL if not found
}