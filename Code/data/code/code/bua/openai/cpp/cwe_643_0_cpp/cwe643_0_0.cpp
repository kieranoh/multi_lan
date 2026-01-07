#include <string>
#include <map>
#include <iostream>
#include <pugixml.hpp>

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> student_info;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml_data.c_str());

    if (!result) {
        std::cerr << "XML parsed with errors\n";
        return student_info; // Return empty map on parse failure
    }

    pugi::xml_node students = doc.child("students");

    for (pugi::xml_node student = students.child("student"); student; student = student.next_sibling("student")) {
        std::string user = student.child_value("username");
        std::string pass = student.child_value("password");

        if (user == username && pass == password) {
            student_info["name"] = student.child_value("name");
            student_info["age"] = student.child_value("age");
            student_info["citizenship"] = student.child_value("citizenship");
            break; // Student found, exit loop
        }
    }

    return student_info; // Return the found student info or empty map
}