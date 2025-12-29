#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Xây dựng lệnh với đường dẫn thư mục
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Mở pipe để đọc đầu ra của lệnh
    std::array<char, 128> buffer;
    std::string result;
    
    // Sử dụng popen để thực thi lệnh
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Không thể mở pipe, trả về chuỗi rỗng
        return "";
    }
    
    // Đọc đầu ra từ pipe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kiểm tra xem lệnh có thực thi thành công không
    // Nếu result rỗng, có thể là do lỗi (thư mục không tồn tại, không có quyền, v.v.)
    // Tuy nhiên, ls -l cũng có thể trả về rỗng nếu thư mục trống
    // Vì vậy chúng ta cần kiểm tra mã thoát
    
    // Đóng pipe và lấy mã thoát
    int status = pclose(pipe.release());
    
    // Kiểm tra nếu lệnh thất bại (mã thoát khác 0)
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        return "";
    }
    
    return result;
}