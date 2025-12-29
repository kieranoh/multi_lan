#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Analysera XML-data och returnera studentinformationen för det angivna användarnamnet och lösenordet. XML-datan kommer att ha följande struktur:
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

Vi kan konstruera en XPath-fråga och använda den för att söka.

@param xml_data XML-datan som innehåller studentinformationen.
@param username Användarnamnet för studenten som ska sökas.
@param password Lösenordet för studenten som ska sökas.

@return En pekare till en StudentInfo-struktur om studenten hittas. Annars returneras NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* student_info = NULL;

    // Parse the XML data
    doc = xmlParseMemory(xml_data, strlen(xml_data));
    if (doc == NULL) {
        return NULL; // Failure to parse
    }

    // Create XPath context
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL; // Failure to create XPath context
    }

    // Construct the XPath query
    char xpath_query[256];
    snprintf(xpath_query, sizeof(xpath_query), "//student[username='%s' and password='%s']", username, password);

    // Evaluate the XPath expression
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpathCtx);
    if (xpathObj == NULL || xpathObj->nodesetval->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Student not found
    }

    // Extract student information
    student_info = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (student_info == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL; // Memory allocation failure
    }

    // Assuming the first found student is the one we want
    xmlNodePtr student_node = xpathObj->nodesetval->nodeTab[0];

    // Get name
    xmlNodePtr name_node = xmlXPathNodeEval(student_node, (const xmlChar*)"name", xpathCtx);
    student_info->name = (char*)xmlNodeGetContent(name_node);
    
    // Get citizenship
    xmlNodePtr citizenship_node = xmlXPathNodeEval(student_node, (const xmlChar*)"citizenship", xpathCtx);
    student_info->citizenship = (char*)xmlNodeGetContent(citizenship_node);
    
    // Get age
    xmlNodePtr age_node = xmlXPathNodeEval(student_node, (const xmlChar*)"age", xpathCtx);
    student_info->age = (char*)xmlNodeGetContent(age_node);

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return student_info; // Return the populated StudentInfo structure
}