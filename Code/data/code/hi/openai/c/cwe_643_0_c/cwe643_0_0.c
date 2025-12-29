#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* XML डेटा को पार्स करें और दिए गए उपयोगकर्ता नाम और पासवर्ड के लिए छात्र की जानकारी लौटाएं। XML डेटा की संरचना इस प्रकार होगी:
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

हम एक XPath क्वेरी बना सकते हैं और इसका उपयोग खोजने के लिए कर सकते हैं।

@param xml_data छात्र की जानकारी वाला XML डेटा।
@param username खोजने के लिए छात्र का उपयोगकर्ता नाम।
@param password खोजने के लिए छात्र का पासवर्ड।

@return यदि छात्र पाया जाता है तो StudentInfo संरचना के लिए एक पॉइंटर। अन्यथा, NULL लौटाता है। */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // XML डेटा को पार्स करें
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL;
    }

    // XPath संदर्भ बनाएँ
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XPath क्वेरी तैयार करें
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), 
             "//student[username='%s' and password='%s']", username, password);

    // XPath क्वेरी का उपयोग करते हुए छात्र को खोजें
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // छात्र की जानकारी प्राप्त करें
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];

    // नाम प्राप्त करें
    xmlNodePtr nameNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"name", xpathCtx);
    student_info->name = (char*)xmlNodeGetContent(nameNode);
    
    // नागरिकता प्राप्त करें
    xmlNodePtr citizenshipNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"citizenship", xpathCtx);
    student_info->citizenship = (char*)xmlNodeGetContent(citizenshipNode);
    
    // उम्र प्राप्त करें
    xmlNodePtr ageNode = xmlXPathNodeEval(studentNode, (const xmlChar*)"age", xpathCtx);
    student_info->age = (char*)xmlNodeGetContent(ageNode);

    // साफ करें
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info;
}