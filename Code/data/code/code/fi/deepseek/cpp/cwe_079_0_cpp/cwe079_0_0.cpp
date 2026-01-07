#include <string>
#include <sstream>

std::string get_welcome_message(const std::string &username) {
    std::ostringstream welcome_stream;
    welcome_stream << "Tervetuloa, " << username << "!";
    return welcome_stream.str();
}