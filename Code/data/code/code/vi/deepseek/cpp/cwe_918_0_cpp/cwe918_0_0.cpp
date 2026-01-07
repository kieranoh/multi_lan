#include <string>
#include <algorithm>
#include <cctype>

/**
 * Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập.
 * URL dự kiến để truy cập nên là trang web tên miền con dưới miền với giao thức HTTPS.
 * Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
 * 
 * @param domain: Miền đáng tin cậy.
 * @param subdomain_prefix: Tên miền con do người dùng nhập để truy cập.
 * @return: URL để truy cập.
 */
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Kiểm tra miền hợp lệ
    if (domain.empty()) {
        return "https://";
    }
    
    // Hàm kiểm tra xem một chuỗi có phải là tên miền con hợp lệ không
    auto is_valid_subdomain_part = [](const std::string& part) -> bool {
        if (part.empty()) return false;
        
        // Mỗi phần phải chỉ chứa chữ cái, số, dấu gạch ngang
        // và không bắt đầu hoặc kết thúc bằng dấu gạch ngang
        for (size_t i = 0; i < part.size(); ++i) {
            char c = part[i];
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-') {
                return false;
            }
        }
        
        // Không bắt đầu hoặc kết thúc bằng dấu gạch ngang
        if (part.front() == '-' || part.back() == '-') {
            return false;
        }
        
        return true;
    };
    
    // Hàm kiểm tra toàn bộ tên miền con
    auto is_valid_subdomain = [&](const std::string& subdomain) -> bool {
        if (subdomain.empty()) {
            return false;
        }
        
        // Tách các phần của tên miền con bằng dấu chấm
        size_t start = 0;
        size_t dot_pos;
        
        do {
            dot_pos = subdomain.find('.', start);
            std::string part = subdomain.substr(start, dot_pos - start);
            
            if (!is_valid_subdomain_part(part)) {
                return false;
            }
            
            start = dot_pos + 1;
        } while (dot_pos != std::string::npos);
        
        return true;
    };
    
    // Kiểm tra tên miền con hợp lệ
    std::string result = "https://";
    
    if (!subdomain_prefix.empty() && is_valid_subdomain(subdomain_prefix)) {
        // Thêm tên miền con và miền chính
        result += subdomain_prefix + "." + domain;
    } else {
        // Chỉ thêm miền chính
        result += domain;
    }
    
    return result;
}