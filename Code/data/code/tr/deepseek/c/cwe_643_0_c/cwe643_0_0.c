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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    StudentInfo* result = NULL;
    
    if (!xml_data || !username || !password) {
        return NULL;
    }
    
    // XML verisini ayrıştır
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }
    
    // XPath bağlamı oluştur
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // XPath ifadesini oluştur: belirtilen kullanıcı adı ve şifreye sahip öğrenciyi bul
    char xpath_expr[512];
    snprintf(xpath_expr, sizeof(xpath_expr), 
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // XPath sorgusunu çalıştır
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_expr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval == NULL || 
        xpathObj->nodesetval->nodeNr == 0) {
        // Öğrenci bulunamadı
        if (xpathObj) xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // İlk eşleşen öğrenci düğümünü al
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    
    // StudentInfo yapısı için bellek ayır
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    // Alanları NULL ile başlat
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // Öğrenci düğümünün alt öğelerini işle
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
    
    // Tüm alanlar başarıyla alındı mı kontrol et
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // Eksik alan varsa bellekleri serbest bırak
        if (result->name) free(result->name);
        if (result->age) free(result->age);
        if (result->citizenship) free(result->citizenship);
        free(result);
        result = NULL;
    }
    
    // Temizlik
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    
    return result;
}