#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 uyumlu e-posta doğrulama deseni
    // Bu desen çoğu geçerli e-posta adresini kabul ederken basit hataları yakalar
    std::string pattern = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    try {
        std::regex email_regex(pattern);
        
        // Temel uzunluk kontrolleri
        if (email.empty() || email.length() > 254) {  // RFC 5321 maksimum uzunluk
            return std::make_tuple(false, pattern);
        }
        
        // @ işareti kontrolü
        size_t at_pos = email.find('@');
        if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
            return std::make_tuple(false, pattern);
        }
        
        // Yerel kısım ve domain kısmını ayır
        std::string local_part = email.substr(0, at_pos);
        std::string domain_part = email.substr(at_pos + 1);
        
        // Yerel kısım ve domain kısmı için ek kontroller
        if (local_part.empty() || local_part.length() > 64 ||  // RFC 5321 yerel kısım maksimumu
            domain_part.empty() || domain_part.length() > 253) {  // Domain maksimum uzunluk
            return std::make_tuple(false, pattern);
        }
        
        // Nokta kontrolleri
        if (local_part.front() == '.' || local_part.back() == '.' ||
            domain_part.front() == '.' || domain_part.back() == '.') {
            return std::make_tuple(false, pattern);
        }
        
        // Ardışık nokta kontrolü
        if (local_part.find("..") != std::string::npos ||
            domain_part.find("..") != std::string::npos) {
            return std::make_tuple(false, pattern);
        }
        
        // Domain kısmında en az bir nokta olmalı
        if (domain_part.find('.') == std::string::npos) {
            return std::make_tuple(false, pattern);
        }
        
        // Domain kısmındaki her etiketin uzunluğu kontrolü
        size_t start = 0;
        size_t end = domain_part.find('.');
        while (end != std::string::npos) {
            std::string label = domain_part.substr(start, end - start);
            if (label.empty() || label.length() > 63) {
                return std::make_tuple(false, pattern);
            }
            start = end + 1;
            end = domain_part.find('.', start);
        }
        
        // Son etiket kontrolü
        std::string last_label = domain_part.substr(start);
        if (last_label.empty() || last_label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        
        // Son etiketin sadece harf içermesi kontrolü (TLD için)
        if (!std::all_of(last_label.begin(), last_label.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        })) {
            return std::make_tuple(false, pattern);
        }
        
        // Regex eşleştirme
        bool is_valid = std::regex_match(email, email_regex);
        
        return std::make_tuple(is_valid, pattern);
        
    } catch (const std::regex_error& e) {
        // Regex hatası durumunda
        return std::make_tuple(false, pattern);
    }
}