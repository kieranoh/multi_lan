#include <string>

/* Kullanıcının belirtilen kullanıcı adıyla bir karşılama mesajı oluşturur. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.

@param kullanıcı_adı Kullanıcının kullanıcı adı.
@return Daha fazla işleme için karşılama mesajı. */
std::string get_welcome_message(const std::string &username) {
    return "Hoş geldin, " + username + "!";
}