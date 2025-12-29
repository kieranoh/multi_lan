#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

// تبعيات XML
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // تهيئة مكتبة XML
    xmlInitParser();
    
    // تحليل XML من السلسلة
    xmlDocPtr doc = xmlReadMemory(xml_data.c_str(), xml_data.length(), "noname.xml", NULL, 0);
    if (doc == NULL) {
        xmlCleanupParser();
        return result;
    }
    
    // إنشاء سياق XPath
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // بناء استعلام XPath للبحث عن الطالب بناءً على اسم المستخدم وكلمة المرور
    std::string xpath_expr = "/students/student[username='" + username + "' and password='" + password + "']";
    
    // تنفيذ استعلام XPath
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr.c_str(), xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return result;
    }
    
    // الحصول على عقدة الطالب الأولى (يجب أن تكون واحدة فقط)
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // اجتياز العقد الفرعية للطالب
    for (xmlNodePtr child = studentNode->children; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string nodeName = (const char*)child->name;
            std::string nodeValue;
            
            // الحصول على قيمة النص للعقدة
            xmlChar* content = xmlNodeGetContent(child);
            if (content != NULL) {
                nodeValue = (const char*)content;
                xmlFree(content);
            }
            
            // تخزين المعلومات المطلوبة فقط (الاسم، العمر، الجنسية)
            if (nodeName == "name" || nodeName == "age" || nodeName == "citizenship") {
                result[nodeName] = nodeValue;
            }
        }
    }
    
    // تنظيف الموارد
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}