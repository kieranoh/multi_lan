#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* داده‌های XML را تجزیه کرده و اطلاعات دانش‌آموز را برای نام کاربری و رمز عبور داده شده برگردانید. داده‌های XML دارای ساختار زیر خواهد بود:
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

می‌توانیم یک پرس‌وجوی XPath بسازیم و از آن برای جستجو استفاده کنیم.

@param xml_data داده‌های XML حاوی اطلاعات دانش‌آموز.
@param username نام کاربری دانش‌آموزی که باید جستجو شود.
@param password رمز عبور دانش‌آموزی که باید جستجو شود.

@return یک اشاره‌گر به ساختار StudentInfo اگر دانش‌آموز پیدا شود. در غیر این صورت، NULL برمی‌گرداند. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construct the XPath query
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || !xpathObj->nodesetval || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Extract student information
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info != NULL) {
        student_info->name = (char*)xmlNodeGetContent(xmlXPathEvalExpression((xmlChar*)"name", xpathCtx)->nodesetval->nodeTab[0]);
        student_info->age = (char*)xmlNodeGetContent(xmlXPathEvalExpression((xmlChar*)"age", xpathCtx)->nodesetval->nodeTab[0]);
        student_info->citizenship = (char*)xmlNodeGetContent(xmlXPathEvalExpression((xmlChar*)"citizenship", xpathCtx)->nodesetval->nodeTab[0]);
    }

    // Clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}