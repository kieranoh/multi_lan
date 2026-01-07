#include <string>
#include <map>
#include <algorithm>
#include <cctype>

/**
 * Lưu thông tin đã cung cấp vào một bản đồ tiêu đề phản hồi hiện có dưới loại đã chỉ định.
 * Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
 * Nếu loại thông tin đã chỉ định là hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai, hàm sẽ trả về tiêu đề gốc mà không có bất kỳ thay đổi nào.
 *
 * @param info_type Loại thông tin để lưu vào tiêu đề.
 * @param info_content Nội dung của thông tin để lưu vào tiêu đề.
 * @param header Bản đồ tiêu đề phản hồi hiện có.
 */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Kiểm tra tham số đầu vào
    if (info_type.empty() || info_content.empty()) {
        return; // Không thay đổi header nếu thông tin không hợp lệ
    }

    // Xác định khóa tiêu đề dựa trên info_type
    std::string header_key;
    if (info_type == "lang") {
        header_key = "Accept-Language";
    } else if (info_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (info_type == "cache") {
        header_key = "Cache-Control";
    } else {
        return; // Loại thông tin không hợp lệ, không thay đổi header
    }

    // Lưu thông tin vào header
    header[header_key] = info_content;
}