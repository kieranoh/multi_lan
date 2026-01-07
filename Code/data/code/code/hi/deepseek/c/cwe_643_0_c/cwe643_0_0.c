#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

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
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    StudentInfo* result = NULL;
    
    // XML पार्सिंग के लिए लाइब्रेरी इनिशियलाइज़ करें
    xmlInitParser();
    
    // मेमोरी में XML डेटा पार्स करें
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        goto cleanup;
    }
    
    // XPath कॉन्टेक्स्ट बनाएं
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        goto cleanup;
    }
    
    // XPath क्वेरी बनाएं: उस student नोड को ढूंढें जिसमें दिए गए username और password हैं
    char xpath_query[512];
    snprintf(xpath_query, sizeof(xpath_query), 
             "/students/student[username='%s' and password='%s']",
             username, password);
    
    // XPath क्वेरी निष्पादित करें
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL) {
        goto cleanup;
    }
    
    // परिणाम प्राप्त करें
    nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        goto cleanup; // कोई मिलान नहीं मिला
    }
    
    // पहला मिलान student नोड लें (केवल एक होना चाहिए)
    xmlNodePtr studentNode = nodes->nodeTab[0];
    
    // StudentInfo संरचना के लिए मेमोरी आवंटित करें
    result = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (result == NULL) {
        goto cleanup;
    }
    
    // संरचना के सदस्यों को NULL से इनिशियलाइज़ करें
    result->name = NULL;
    result->age = NULL;
    result->citizenship = NULL;
    
    // student नोड के चिल्ड्रन को पार्स करें
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
    
    // सभी आवश्यक फ़ील्ड मिल गए हैं यह सुनिश्चित करें
    if (result->name == NULL || result->age == NULL || result->citizenship == NULL) {
        // कुछ फ़ील्ड गुम हैं, मेमोरी मुक्त करें और NULL लौटाएं
        if (result->name != NULL) free(result->name);
        if (result->age != NULL) free(result->age);
        if (result->citizenship != NULL) free(result->citizenship);
        free(result);
        result = NULL;
    }

cleanup:
    // XPath ऑब्जेक्ट मुक्त करें
    if (xpathObj != NULL) {
        xmlXPathFreeObject(xpathObj);
    }
    
    // XPath कॉन्टेक्स्ट मुक्त करें
    if (xpathCtx != NULL) {
        xmlXPathFreeContext(xpathCtx);
    }
    
    // XML डॉक्यूमेंट मुक्त करें
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // XML पार्सर क्लीनअप
    xmlCleanupParser();
    
    return result;
}