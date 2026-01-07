#include <tuple>
#include <string>
#include <regex>

/* Kiểm tra xem địa chỉ email được cung cấp có hợp lệ hay không. Ví dụ, abc.123@def.ghi.com.uk là một địa chỉ email hợp lệ. Bao phủ càng nhiều trường hợp càng tốt để tránh kết quả sai lệch.

@param email Địa chỉ email cần kiểm tra
@return Một tuple với phần tử đầu tiên là một boolean cho biết email có hợp lệ hay không và phần tử thứ hai là mẫu được sử dụng để kiểm tra email. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Mẫu regex để kiểm tra địa chỉ email
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}