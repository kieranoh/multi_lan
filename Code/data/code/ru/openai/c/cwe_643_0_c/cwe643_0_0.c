#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

typedef struct {
    char* name;
    char* age;
    char* citizenship;
} StudentInfo;

/* Парсите XML-данные и возвращайте информацию о студенте для данного имени пользователя и пароля. XML-данные будут иметь следующую структуру:
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

@param xml_data XML-данные, содержащие информацию о студенте.
@param username Имя пользователя студента, которого нужно найти.
@param password Пароль студента, которого нужно найти.

@return Указатель на структуру StudentInfo, если студент найден. В противном случае возвращает NULL. */
StudentInfo* get_student_info(const char* xml_data, const char* username, const char* password) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    StudentInfo* studentInfo = NULL;

    // Парсим XML данные
    doc = xmlReadMemory(xml_data, strlen(xml_data), NULL, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    // Создаем XPath контекст
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // Создаем XPath запрос для поиска студента
    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "/students/student[username='%s' and password='%s']", username, password);
    
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL || xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Получаем информацию о студенте
    studentInfo = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (studentInfo == NULL) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    // Извлекаем данные о студенте
    xmlNodePtr studentNode = xpathObj->nodesetval->nodeTab[0];
    for (xmlNodePtr currNode = studentNode->children; currNode; currNode = currNode->next) {
        if (currNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(currNode->name, (const xmlChar *)"name") == 0) {
                studentInfo->name = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"age") == 0) {
                studentInfo->age = (char*)xmlNodeGetContent(currNode);
            } else if (xmlStrcmp(currNode->name, (const xmlChar *)"citizenship") == 0) {
                studentInfo->citizenship = (char*)xmlNodeGetContent(currNode);
            }
        }
    }

    // Освобождаем память и возвращаем информацию о студенте
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return studentInfo; 
}