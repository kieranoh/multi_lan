#include <string>
#include <map>
#include <pugixml.hpp>

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

@return यदि पाया गया, तो छात्र की जानकारी (नाम, उम्र, नागरिकता) वाला एक मानचित्र, अन्यथा एक खाली मानचित्र। */
std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml_data.c_str());

    if (!result) {
        return student_info; // Return empty map if XML parsing fails
    }

    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";
    pugi::xml_node student_node = doc.select_node(xpath_query.c_str()).node();

    if (student_node) {
        student_info["name"] = student_node.child("name").text().as_string();
        student_info["age"] = student_node.child("age").text().as_string();
        student_info["citizenship"] = student_node.child("citizenship").text().as_string();
    }

    return student_info;
}