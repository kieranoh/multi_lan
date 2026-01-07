#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Kiểm tra đầu vào rỗng
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Hàm phụ trợ để chuyển đổi chuỗi thành chữ thường
    auto to_lower = [](const std::string& str) -> std::string {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    };
    
    // Chuẩn hóa domain: chuyển thành chữ thường và loại bỏ khoảng trắng
    std::string normalized_domain = to_lower(domain);
    normalized_domain.erase(std::remove_if(normalized_domain.begin(), normalized_domain.end(),
                                          [](unsigned char c) { return std::isspace(c); }),
                           normalized_domain.end());
    
    // Kiểm tra xem target có bắt đầu bằng "https://" không
    std::string lower_target = to_lower(target);
    const std::string https_prefix = "https://";
    
    // Nếu target không bắt đầu bằng https://, thêm vào
    std::string processed_target;
    if (lower_target.find(https_prefix) == 0) {
        processed_target = target; // Giữ nguyên target gốc (bao gồm cả chữ hoa/thường)
    } else {
        // Nếu target bắt đầu bằng http://, thay thế bằng https://
        const std::string http_prefix = "http://";
        if (lower_target.find(http_prefix) == 0) {
            processed_target = "https://" + target.substr(http_prefix.length());
        } else {
            // Nếu không có giao thức nào, thêm https://
            processed_target = "https://" + target;
        }
    }
    
    // Trích xuất host từ processed_target
    std::string target_host;
    std::string processed_target_lower = to_lower(processed_target);
    
    // Tìm vị trí bắt đầu của host (sau "https://")
    size_t host_start = processed_target_lower.find(https_prefix);
    if (host_start == std::string::npos) {
        // Nếu không tìm thấy (không nên xảy ra), trả về domain mặc định
        return "https://" + normalized_domain;
    }
    
    host_start += https_prefix.length();
    
    // Tìm vị trí kết thúc của host (trước '/' đầu tiên hoặc kết thúc chuỗi)
    size_t host_end = processed_target_lower.find('/', host_start);
    if (host_end == std::string::npos) {
        host_end = processed_target_lower.length();
    }
    
    target_host = processed_target_lower.substr(host_start, host_end - host_start);
    
    // Kiểm tra xem target_host có kết thúc bằng domain không
    // So sánh từ cuối chuỗi: target_host phải bằng domain hoặc kết thúc bằng "." + domain
    bool is_same_domain = false;
    
    if (target_host == normalized_domain) {
        is_same_domain = true;
    } else if (target_host.length() > normalized_domain.length() + 1) {
        // Kiểm tra xem target_host có kết thúc bằng "." + domain không
        size_t dot_pos = target_host.length() - normalized_domain.length() - 1;
        if (target_host[dot_pos] == '.' && 
            target_host.substr(dot_pos + 1) == normalized_domain) {
            is_same_domain = true;
        }
    }
    
    // Trả về kết quả
    if (is_same_domain) {
        return processed_target;
    } else {
        return "https://" + normalized_domain;
    }
}