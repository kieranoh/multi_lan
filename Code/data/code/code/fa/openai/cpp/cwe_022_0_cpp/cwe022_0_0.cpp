#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

/* 
با توجه به مسیر دایرکتوری ارائه‌شده توسط کاربر و نام فایل، فایل را از دایرکتوری بخوانید و محتوای آن را برگردانید. 
اگر در طول فرآیند خواندن فایل خطایی رخ دهد (مانند عدم وجود فایل، خطای دسترسی)، یک رشته خالی برگردانید.

@param filename نام فایلی که باید خوانده شود، که توسط کاربر درخواست شده است.
@param dir_path مسیر دایرکتوری که فایل در آن قرار دارد.

@return محتوای فایل در صورتی که وجود داشته باشد و قابل دسترسی باشد، در غیر این صورت یک رشته خالی. 
*/
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::ifstream file(dir_path + "/" + filename);
    if (!file.is_open()) {
        return ""; // اگر فایل باز نشود، رشته خالی برگردانید
    }

    std::ostringstream buffer;
    buffer << file.rdbuf(); // محتوای فایل را به بافر اضافه کنید
    return buffer.str(); // محتوای خوانده شده را برگردانید
}