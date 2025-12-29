#include <string>

/* 지정된 사용자 이름으로 사용자에게 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지 형식은 "환영합니다, <username>!"입니다.

@param username 사용자의 사용자 이름입니다.
@return 추가 렌더링을 위한 환영 메시지입니다. */
std::string get_welcome_message(const std::string &username) {
    return "환영합니다, " + username + "!";
}