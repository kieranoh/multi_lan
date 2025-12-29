#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Mẫu regex chính cho địa chỉ email theo RFC 5322
    std::string pattern = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // Kiểm tra độ dài tối đa (theo RFC 5321)
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra ký tự @
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // Tách local-part và domain
    std::string local_part = email.substr(0, at_pos);
    std::string domain = email.substr(at_pos + 1);
    
    // Kiểm tra độ dài local-part (tối đa 64 ký tự theo RFC 5321)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra domain không rỗng
    if (domain.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra domain không bắt đầu hoặc kết thúc bằng dấu chấm
    if (domain.front() == '.' || domain.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra không có hai dấu chấm liên tiếp trong domain
    if (domain.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra các ký tự không hợp lệ trong domain
    for (char c : domain) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, pattern);
        }
    }
    
    // Kiểm tra các nhãn domain (giữa các dấu chấm)
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain.find('.', start)) != std::string::npos) {
        std::string label = domain.substr(start, dot_pos - start);
        if (label.empty() || label.length() > 63 || label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        start = dot_pos + 1;
    }
    
    // Kiểm tra nhãn cuối cùng
    std::string last_label = domain.substr(start);
    if (last_label.empty() || last_label.length() > 63 || last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra TLD (Top-Level Domain) có ít nhất 2 ký tự
    if (last_label.length() < 2) {
        return std::make_tuple(false, pattern);
    }
    
    // Áp dụng regex để kiểm tra tổng thể
    try {
        std::regex email_regex(pattern);
        if (!std::regex_match(email, email_regex)) {
            return std::make_tuple(false, pattern);
        }
    } catch (const std::regex_error&) {
        // Nếu regex không hợp lệ, trả về false
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra bổ sung cho local-part
    // Không được bắt đầu hoặc kết thúc bằng dấu chấm
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Không được có hai dấu chấm liên tiếp trong local-part
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Kiểm tra các ký tự trích dẫn (quoted strings) - đơn giản hóa
    // Nếu local-part có dấu ngoặc kép, kiểm tra cặp
    size_t quote_count = std::count(local_part.begin(), local_part.end(), '"');
    if (quote_count > 0) {
        if (quote_count % 2 != 0 || local_part.front() != '"' || local_part.back() != '"') {
            return std::make_tuple(false, pattern);
        }
    }
    
    return std::make_tuple(true, pattern);
}