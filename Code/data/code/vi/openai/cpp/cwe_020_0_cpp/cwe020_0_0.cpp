#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Kiểm tra xem chuỗi URL mục tiêu có chứa miền không
    if (target.find(domain) != std::string::npos) {
        return target; // Nếu có, trả về URL mục tiêu
    } else {
        return "https://" + domain; // Nếu không, trả về URL miền
    }
}