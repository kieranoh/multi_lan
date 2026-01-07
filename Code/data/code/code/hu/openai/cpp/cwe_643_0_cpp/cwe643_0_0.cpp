#include <iostream>
#include <map>
#include <string>
#include <pugixml.hpp>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;
    
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml_data.c_str());

    if (!result) {
        return student_info; // Return empty map if XML parsing fails
    }

    pugi::xml_node students = doc.child("students");
    for (pugi::xml_node student = students.child("student"); student; student = student.next_sibling("student")) {
        std::string user = student.child("username").text().as_string();
        std::string pass = student.child("password").text().as_string();

        if (user == username && pass == password) {
            student_info["name"] = student.child("name").text().as_string();
            student_info["citizenship"] = student.child("citizenship").text().as_string();
            student_info["age"] = student.child("age").text().as_string();
            break; // Student found, break the loop
        }
    }

    return student_info; // Return the found student info or an empty map
}