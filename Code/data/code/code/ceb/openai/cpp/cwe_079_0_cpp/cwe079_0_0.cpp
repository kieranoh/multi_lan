#include <string>

/* 지정된 사용자 이름으로 사용자를 위한 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지는 "환영합니다, <username>!" 형식입니다. */
std::string get_welcome_message(const std::string &username) {
    return "환영합니다, " + username + "!";
}