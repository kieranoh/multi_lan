#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün. XML verisi aşağıdaki yapıya sahip olacaktır:
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

Bir XPath sorgusu oluşturabiliriz ve bunu arama yapmak için kullanabiliriz.

@param xml_data Öğrenci bilgilerini içeren XML verisi.
@param username Aranacak öğrencinin kullanıcı adı.
@param password Aranacak öğrencinin şifresi.

@return Öğrenci bulunursa bir StudentInfo yapısına işaretçi. Aksi takdirde, NULL döner. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // XML verisini ayrıştır
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    // XPath bağlamını oluştur
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath sorgusunu oluştur
    char query[256];
    snprintf(query, sizeof(query), "/students/student[username='%s' and password='%s']", username, password);

    // XPath sorgusunu uygula
    xpathObj = xmlXPathEvalExpression((const xmlChar*)query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Öğrenci bilgilerini al
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr currNode = studentNode->children; currNode; currNode = currNode->next) {
        if (currNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(currNode->name, (const xmlChar *)"name") == 0) {
                student_info->name = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"age") == 0) {
                student_info->age = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"citizenship") == 0) {
                student_info->citizenship = (char*)xmlNodeGetContent(currNode);
            }
        }
    }

    // Temizlik
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}