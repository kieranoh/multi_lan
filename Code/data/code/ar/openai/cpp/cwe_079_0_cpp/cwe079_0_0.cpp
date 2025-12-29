#include <string>

/* يولد رسالة ترحيب للمستخدم بالاسم المستخدم المحدد. ستظهر هذه الرسالة على صفحة HTML بعد تسجيل دخول المستخدم. ستكون الرسالة بالشكل "مرحبًا، <username>!".

@param username اسم المستخدم للمستخدم.
@return رسالة الترحيب للتقديم لاحقًا. */
std::string get_welcome_message(const std::string &username) {
    return "مرحبًا، " + username + "!";
}