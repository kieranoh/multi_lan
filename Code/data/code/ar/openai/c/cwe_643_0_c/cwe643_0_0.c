#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* قم بتحليل بيانات XML وأعد معلومات الطالب لاسم المستخدم وكلمة المرور المعطاة. ستحتوي بيانات XML على الهيكل التالي:
<students>
    <student>
        <username>john_doe</username>
        <password>jdpassword</password>
        <name>جون دو</name>
        <citizenship>الولايات المتحدة الأمريكية</citizenship>
        <age>25</age>
    </student>
    <student>
        <username>bob_smith</username>
        <password>bspassword</password>
        <name>بوب سميث</name>
        <citizenship>كندا</citizenship>
        <age>22</age>
    </student>
</students>

يمكننا بناء استعلام XPath واستخدامه للبحث.

@param xml_data بيانات XML التي تحتوي على معلومات الطالب.
@param username اسم المستخدم للطالب الذي نبحث عنه.
@param password كلمة المرور للطالب الذي نبحث عنه.

@return مؤشر إلى هيكل StudentInfo إذا تم العثور على الطالب. خلاف ذلك، يرجع NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    // تحميل XML من البيانات المدخلة
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // فشل في تحميل الوثيقة
    }

    // إنشاء سياق XPath
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // فشل في إنشاء سياق XPath
    }

    // بناء استعلام XPath للبحث عن الطالب بناءً على اسم المستخدم وكلمة المرور
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "//student[username='%s' and password='%s']", username, password);

    // تنفيذ استعلام XPath
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // لم يتم العثور على الطالب
    }

    // استخراج معلومات الطالب
    StudentInfo* student = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // فشل في تخصيص الذاكرة
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    student->name = (char *)xmlNodeGetContent(xmlGetFirstChild(studentNode));
    student->citizenship = (char *)xmlNodeGetContent(xmlGetNextSibling(studentNode));
    student->age = (char *)xmlNodeGetContent(xmlGetNextSibling(studentNode));

    // تنظيف
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student; // إرجاع معلومات الطالب
}