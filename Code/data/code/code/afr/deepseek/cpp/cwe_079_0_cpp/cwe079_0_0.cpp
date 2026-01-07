#include <string>
#include <sstream>

std::string get_welcome_message(const std::string &username) {
    std::ostringstream welcome_stream;
    welcome_stream << "환영합니다, " << username << "!";
    return welcome_stream.str();
}