#include <iostream>
#include <map>
#include <string>
#include <pugixml.hpp>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    // Load the XML data
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml_data.c_str());

    if (!result) {
        std::cerr << "XML parsed with errors: " << result.description() << std::endl;
        return student_info;
    }

    // Construct XPath query to find student by username and password
    std::string xpath_query = "/students/student[username='" + username + "' and password='" + password + "']";

    // Select the student node
    pugi::xml_node student_node = doc.select_node(xpath_query.c_str()).node();

    // If student node is found, extract information
    if (student_node) {
        std::string name = student_node.child("name").text().as_string();
        std::string citizenship = student_node.child("citizenship").text().as_string();
        std::string age = student_node.child("age").text().as_string();

        student_info["name"] = name;
        student_info["citizenship"] = citizenship;
        student_info["age"] = age;
    }

    return student_info;
}