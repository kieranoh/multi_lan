#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>

// PugiXML kütüphanesi için forward declaration
namespace pugi {
    class xml_document;
    class xml_node;
}

std::map<std::string, std::string> get_student_info(const std::string& xml_data, 
                                                   const std::string& username, 
                                                   const std::string& password) {
    std::map<std::string, std::string> result;
    
    try {
        // PugiXML başlık dosyasını dahil et
        #include "pugixml.hpp"
        
        pugi::xml_document doc;
        pugi::xml_parse_result parse_result = doc.load_string(xml_data.c_str());
        
        if (!parse_result) {
            // XML ayrıştırma başarısız oldu, boş harita döndür
            return result;
        }
        
        // XPath sorgusu oluştur
        std::stringstream xpath_query;
        xpath_query << "/students/student[username='" << username 
                   << "' and password='" << password << "']";
        
        // XPath sorgusunu çalıştır
        pugi::xpath_node_set students = doc.select_nodes(xpath_query.str().c_str());
        
        if (students.empty()) {
            // Öğrenci bulunamadı, boş harita döndür
            return result;
        }
        
        // İlk eşleşen öğrenciyi al (genellikle sadece bir tane olmalı)
        pugi::xml_node student_node = students[0].node();
        
        // Öğrenci bilgilerini haritaya ekle
        pugi::xml_node name_node = student_node.child("name");
        if (name_node) {
            result["name"] = name_node.text().get();
        }
        
        pugi::xml_node citizenship_node = student_node.child("citizenship");
        if (citizenship_node) {
            result["citizenship"] = citizenship_node.text().get();
        }
        
        pugi::xml_node age_node = student_node.child("age");
        if (age_node) {
            result["age"] = age_node.text().get();
        }
        
    } catch (const std::exception& e) {
        // Herhangi bir istisna durumunda boş harita döndür
        return result;
    } catch (...) {
        // Bilinmeyen istisna durumunda boş harita döndür
        return result;
    }
    
    return result;
}