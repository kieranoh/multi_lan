#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Lấy thời gian hiện tại
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Chuyển đổi sang định dạng thời gian ISO
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");

    // Tạo chuỗi nhật ký
    std::string log_entry = "[" + oss.str() + "] Nhận: " + msg;
    return log_entry;
}