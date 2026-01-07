#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Tạo đường dẫn đầy đủ đến tệp
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Kiểm tra xem tệp có tồn tại và là tệp thông thường không
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Mở tệp để đọc
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return "";
        }
        
        // Lấy kích thước tệp
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Đọc toàn bộ nội dung tệp
        std::string content;
        content.resize(size);
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
    }
    catch (const std::exception&) {
        // Bắt tất cả các ngoại lệ và trả về chuỗi rỗng
        return "";
    }
}