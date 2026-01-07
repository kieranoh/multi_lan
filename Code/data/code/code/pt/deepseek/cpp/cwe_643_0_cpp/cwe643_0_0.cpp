#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// Função auxiliar para dividir uma string por um delimitador
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Função auxiliar para remover espaços em branco do início e fim
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Função auxiliar para extrair conteúdo entre tags
std::string extract_tag_content(const std::string& xml, const std::string& tag_name) {
    std::string open_tag = "<" + tag_name + ">";
    std::string close_tag = "</" + tag_name + ">";
    
    size_t start_pos = xml.find(open_tag);
    if (start_pos == std::string::npos) {
        return "";
    }
    
    size_t end_pos = xml.find(close_tag, start_pos);
    if (end_pos == std::string::npos) {
        return "";
    }
    
    start_pos += open_tag.length();
    return trim(xml.substr(start_pos, end_pos - start_pos));
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> result;
    
    // Encontrar todos os blocos de student
    std::vector<std::string> students;
    std::string search_str = xml_data;
    size_t start_pos = 0;
    
    while (true) {
        size_t student_start = search_str.find("<student>", start_pos);
        if (student_start == std::string::npos) {
            break;
        }
        
        size_t student_end = search_str.find("</student>", student_start);
        if (student_end == std::string::npos) {
            break;
        }
        
        student_end += 10; // Comprimento de "</student>"
        std::string student_block = search_str.substr(student_start, student_end - student_start);
        students.push_back(student_block);
        
        start_pos = student_end;
    }
    
    // Procurar pelo aluno com username e password correspondentes
    for (const auto& student : students) {
        std::string found_username = extract_tag_content(student, "username");
        std::string found_password = extract_tag_content(student, "password");
        
        if (found_username == username && found_password == password) {
            // Extrair as informações do aluno
            std::string name = extract_tag_content(student, "name");
            std::string citizenship = extract_tag_content(student, "citizenship");
            std::string age = extract_tag_content(student, "age");
            
            // Preencher o mapa de resultado
            result["name"] = name;
            result["citizenship"] = citizenship;
            result["age"] = age;
            
            return result;
        }
    }
    
    // Retornar mapa vazio se não encontrado
    return result;
}