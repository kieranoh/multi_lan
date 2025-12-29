#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

/**
 * Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho.
 * Tệp chỉ nên có thể truy cập bởi người dùng hiện tại.
 * 
 * @param directory Thư mục để lưu tệp bí mật.
 * @param filename Tên tệp của tệp bí mật.
 * @param content Nội dung của tệp bí mật.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Kiểm tra thư mục tồn tại, nếu không thì tạo mới
    std::filesystem::path dir_path(directory);
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }
    
    // Tạo đường dẫn đầy đủ đến tệp
    std::filesystem::path file_path = dir_path / filename;
    std::string full_path = file_path.string();
    
    // Mở tệp để ghi (tạo mới hoặc ghi đè)
    std::ofstream out_file(full_path, std::ios::out | std::ios::trunc);
    if (!out_file.is_open()) {
        throw std::runtime_error("Không thể mở tệp để ghi: " + full_path);
    }
    
    // Ghi nội dung vào tệp
    out_file.write(content.c_str(), content.size());
    out_file.close();
    
    if (out_file.fail()) {
        throw std::runtime_error("Lỗi khi ghi nội dung vào tệp: " + full_path);
    }
    
    // Thiết lập quyền truy cập: chỉ người dùng hiện tại có thể đọc/ghi
    // 0600 = rw------- (chủ sở hữu có thể đọc và ghi, không ai khác có quyền)
    if (chmod(full_path.c_str(), S_IRUSR | S_IWUSR) != 0) {
        // Nếu không thể thiết lập quyền, xóa tệp đã tạo và ném ngoại lệ
        std::filesystem::remove(file_path);
        throw std::runtime_error("Không thể thiết lập quyền truy cập cho tệp: " + 
                                std::string(strerror(errno)));
    }
}