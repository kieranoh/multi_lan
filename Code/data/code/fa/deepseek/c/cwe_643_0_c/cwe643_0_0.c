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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpath_ctx = NULL;
    xmlXPathObjectPtr xpath_obj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    // مقداردهی اولیه کتابخانه libxml2
    xmlInitParser();
    
    // تجزیه XML از رشته
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // ایجاد زمینه XPath
    xpath_ctx = xmlXPathNewContext(doc);
    if (xpath_ctx == NULL) {
        goto cleanup;
    }
    
    // ساخت پرس‌وجوی XPath برای یافتن دانش‌آموز با نام کاربری و رمز عبور مشخص
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // اجرای پرس‌وجوی XPath
    xpath_obj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpath_ctx);
    if (xpath_obj == NULL) {
        goto cleanup;
    }
    
    // بررسی نتایج
    nodes = xpath_obj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        goto cleanup;
    }
    
    // فقط اولین دانش‌آموز منطبق را در نظر می‌گیریم
    xmlNodePtr student_node = nodes->nodeTab[0];
    
    // تخصیص حافظه برای ساختار نتیجه
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // مقداردهی اولیه فیلدها
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // پیمایش فرزندان گره student برای استخراج اطلاعات
    xmlNodePtr child = student_node->children;
    while (child != NULL) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
                if (strcmp((const char*)child->name, "name") == 0) {
                    result->name = strdup((const char*)content);
                } else if (strcmp((const char*)child->name, "age") == 0) {
                    result->age = strdup((const char*)content);
                } else if (strcmp((const char*)child->name, "citizenship") == 0) {
                    result->citizenship = strdup((const char*)content);
                }
                xmlFree(content);
            }
        }
        child = child->next;
    }
    
    // بررسی اینکه آیا همه فیلدهای مورد نیاز استخراج شده‌اند
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // اگر برخی فیلدها گم شده‌اند، حافظه را آزاد کرده و NULL برگردان
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // پاکسازی منابع
    if (xpath_obj != NULL) {
        xmlXPathFreeObject(xpath_obj);
    }
    if (xpath_ctx != NULL) {
        xmlXPathFreeContext(xpath_ctx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    xmlCleanupParser();
    
    return result;
}