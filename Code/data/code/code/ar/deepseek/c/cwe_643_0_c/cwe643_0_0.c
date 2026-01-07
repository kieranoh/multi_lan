#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    // تهيئة مكتبة libxml2
    xmlInitParser();
    
    // تحليل بيانات XML
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // إنشاء سياق XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // بناء استعلام XPath للبحث عن الطالب بناءً على اسم المستخدم وكلمة المرور
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query),
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // تنفيذ استعلام XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        goto cleanup;
    }
    
    // استخراج العقدة الأولى (يجب أن تكون هناك عقدة واحدة فقط تطابق)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // تخصيص الذاكرة لهيكل النتيجة
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // تهيئة الحقول
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // اجتياز العقد الفرعية للطالب
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
    
    // التحقق من أن جميع الحقول تم استخراجها بنجاح
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // تنظيف الذاكرة في حالة الفشل
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // تنظيف الموارد
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // تنظيف مكتبة libxml2
    xmlCleanupParser();
    
    return result;
}