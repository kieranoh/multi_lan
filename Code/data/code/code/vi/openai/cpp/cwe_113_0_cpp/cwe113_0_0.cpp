#include <map>
#include <string>

/* Lưu thông tin đã cung cấp vào một bản đồ tiêu đề phản hồi hiện có dưới loại đã chỉ định.
Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
Nếu loại thông tin đã chỉ định là hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai, hàm sẽ trả về tiêu đề gốc mà không có bất kỳ thay đổi nào.

@param info_type Loại thông tin để lưu vào tiêu đề.
@param info_content Nội dung của thông tin để lưu vào tiêu đề.
@param header Bản đồ tiêu đề phản hồi hiện có.

@return Bản đồ tiêu đề phản hồi đã cập nhật với thông tin đã lưu. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Nếu loại thông tin không hợp lệ, không thay đổi header
        return;
    }
}