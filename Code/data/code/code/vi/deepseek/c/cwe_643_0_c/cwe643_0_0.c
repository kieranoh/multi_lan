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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    if (!xml_data || !username || !password) {
        return NULL;
    }
    
    // Khởi tạo thư viện libxml2
    xmlInitParser();
    
    // Phân tích chuỗi XML
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        xmlCleanupParser();
        return NULL;
    }
    
    // Tạo ngữ cảnh XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Xây dựng truy vấn XPath để tìm student với username và password phù hợp
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // Thực thi truy vấn XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // Không tìm thấy sinh viên phù hợp
        if (xpathObj) xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Lấy node student đầu tiên (chỉ có một nếu tìm thấy)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // Cấp phát bộ nhớ cho kết quả
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    // Khởi tạo các trường
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Duyệt qua các node con để lấy thông tin
    xmlNodePtr child = studentNode->children;
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
    
    // Kiểm tra xem tất cả các trường đã được lấy chưa
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Giải phóng bộ nhớ nếu thiếu thông tin
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // Giải phóng tài nguyên
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}