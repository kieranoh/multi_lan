#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/**
 * داده‌های XML را تجزیه کنید و اطلاعات دانش‌آموز را برای نام کاربری و رمز عبور داده شده برگردانید.
 *
 * @param xml_data داده‌های XML حاوی اطلاعات دانش‌آموز.
 * @param username نام کاربری دانش‌آموزی که باید جستجو شود.
 * @param password رمز عبور دانش‌آموزی که باید جستجو شود.
 *
 * @return یک نقشه حاوی اطلاعات دانش‌آموز (نام، سن، تابعیت) در صورت یافتن، در غیر این صورت یک نقشه خالی.
 */
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // مقداردهی اولیه کتابخانه XML
    xmlInitParser();
    
    // تجزیه XML از رشته
    std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc(
        xmlReadMemory(xml_data.c_str(), xml_data.size(), "noname.xml", nullptr, 0),
        xmlFreeDoc
    );
    
    if (!doc) {
        xmlCleanupParser();
        return result;
    }
    
    // ایجاد زمینه XPath
    std::unique_ptr<xmlXPathContext, decltype(&xmlXPathFreeContext)> context(
        xmlXPathNewContext(doc.get()),
        xmlXPathFreeContext
    );
    
    if (!context) {
        xmlCleanupParser();
        return result;
    }
    
    // ساخت پرس‌وجوی XPath برای یافتن دانش‌آموز با نام کاربری و رمز عبور مشخص
    std::string xpath_query = 
        "/students/student[username='" + username + "' and password='" + password + "']";
    
    // اجرای پرس‌وجوی XPath
    std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)> xpath_result(
        xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpath_query.c_str()), context.get()),
        xmlXPathFreeObject
    );
    
    if (!xpath_result || xpath_result->nodesetval == nullptr || xpath_result->nodesetval->nodeNr == 0) {
        xmlCleanupParser();
        return result;
    }
    
    // گرفتن اولین گره دانش‌آموز (باید فقط یک مورد باشد)
    xmlNodePtr student_node = xpath_result->nodesetval->nodeTab[0];
    
    // پیمایش فرزندان گره دانش‌آموز و استخراج اطلاعات
    for (xmlNodePtr child = student_node->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            std::string node_name = reinterpret_cast<const char*>(child->name);
            
            // استخراج محتوای متنی گره
            xmlChar* content = xmlNodeGetContent(child);
            if (content) {
                std::string node_value = reinterpret_cast<const char*>(content);
                xmlFree(content);
                
                // ذخیره اطلاعات مورد نیاز (نام، سن، تابعیت)
                if (node_name == "name" || node_name == "age" || node_name == "citizenship") {
                    result[node_name] = node_value;
                }
            }
        }
    }
    
    xmlCleanupParser();
    return result;
}