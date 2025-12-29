#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>

// Pomoćna funkcija za trimanje stringa
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// Pomoćna funkcija za parsiranje XML-a
std::vector<std::map<std::string, std::string>> parse_xml(const std::string& xml_data) {
    std::vector<std::map<std::string, std::string>> students;
    std::map<std::string, std::string> current_student;
    std::string current_tag;
    std::string current_content;
    bool in_tag = false;
    bool in_content = false;
    bool is_closing_tag = false;
    
    for (size_t i = 0; i < xml_data.length(); i++) {
        char c = xml_data[i];
        
        if (c == '<') {
            // Početak taga
            in_tag = true;
            current_tag.clear();
            is_closing_tag = false;
            
            // Provjeri je li zatvarajući tag
            if (i + 1 < xml_data.length() && xml_data[i + 1] == '/') {
                is_closing_tag = true;
                i++; // Preskoči '/'
            }
        } else if (c == '>') {
            // Kraj taga
            in_tag = false;
            
            if (is_closing_tag) {
                // Ako je zatvarajući tag za studenta, dodaj trenutnog studenta u listu
                if (current_tag == "student") {
                    if (!current_student.empty()) {
                        students.push_back(current_student);
                        current_student.clear();
                    }
                }
                // Resetiraj trenutni sadržaj za sljedeći tag
                current_content.clear();
                in_content = false;
            } else {
                // Početak sadržaja nakon otvarajućeg taga
                in_content = true;
                current_content.clear();
            }
        } else if (in_tag) {
            // Akumuliraj ime taga
            current_tag += c;
        } else if (in_content && !in_tag) {
            // Akumuliraj sadržaj unutar taga
            current_content += c;
            
            // Provjeri je li sljedeći karakter početak novog taga
            if (i + 1 < xml_data.length() && xml_data[i + 1] == '<') {
                // Kraj sadržaja, spremi u trenutnog studenta
                std::string trimmed_content = trim(current_content);
                if (!trimmed_content.empty() && !current_tag.empty()) {
                    current_student[current_tag] = trimmed_content;
                }
                in_content = false;
            }
        }
    }
    
    return students;
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Parsiraj XML podatke
    std::vector<std::map<std::string, std::string>> students = parse_xml(xml_data);
    
    // Traži studenta sa zadanim korisničkim imenom i lozinkom
    for (const auto& student : students) {
        auto username_it = student.find("username");
        auto password_it = student.find("password");
        
        if (username_it != student.end() && password_it != student.end()) {
            if (username_it->second == username && password_it->second == password) {
                // Pronađen student, izdvoji tražene informacije
                auto name_it = student.find("name");
                auto citizenship_it = student.find("citizenship");
                auto age_it = student.find("age");
                
                if (name_it != student.end()) {
                    result["name"] = name_it->second;
                }
                if (citizenship_it != student.end()) {
                    result["citizenship"] = citizenship_it->second;
                }
                if (age_it != student.end()) {
                    result["age"] = age_it->second;
                }
                
                // Dodaj i korisničko ime i lozinku za potpunost
                result["username"] = username_it->second;
                result["password"] = password_it->second;
                
                break; // Pronađen student, prekini pretragu
            }
        }
    }
    
    return result;
}