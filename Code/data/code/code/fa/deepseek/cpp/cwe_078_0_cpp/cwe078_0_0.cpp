#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // ساخت دستور با استفاده از dir_path
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // باز کردن یک pipe برای خواندن خروجی دستور
    std::array<char, 128> buffer;
    std::string result;
    
    // استفاده از popen برای اجرای دستور و خواندن خروجی
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // بررسی موفقیت‌آمیز بودن باز کردن pipe
    if (!pipe) {
        // در صورت شکست، رشته خالی برگردانید
        return "";
    }
    
    // خواندن خروجی دستور
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // حذف کاراکتر newline اضافی در انتها در صورت وجود
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}