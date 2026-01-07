#include <string>
#include <stdexcept>

/**
 * Kullanıcının belirtilen kullanıcı adıyla bir karşılama mesajı oluşturur.
 * Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir.
 * Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.
 *
 * @param kullanıcı_adı Kullanıcının kullanıcı adı.
 * @return Daha fazla işleme için karşılama mesajı.
 * @throw std::invalid_argument Eğer kullanıcı adı boşsa veya sadece boşluklardan oluşuyorsa.
 */
std::string get_welcome_message(const std::string &username) {
    // Kullanıcı adının geçerliliğini kontrol et
    if (username.empty()) {
        throw std::invalid_argument("Kullanıcı adı boş olamaz.");
    }
    
    // Kullanıcı adının sadece boşluklardan oluşup oluşmadığını kontrol et
    bool all_spaces = true;
    for (char c : username) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            all_spaces = false;
            break;
        }
    }
    
    if (all_spaces) {
        throw std::invalid_argument("Kullanıcı adı sadece boşluklardan oluşamaz.");
    }
    
    // Karşılama mesajını oluştur
    return "Hoş geldin, " + username + "!";
}