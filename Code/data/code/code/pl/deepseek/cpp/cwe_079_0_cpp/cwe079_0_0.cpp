#include <string>
#include <sstream>

/**
 * Generuje wiadomość powitalną dla użytkownika z określoną nazwą użytkownika.
 * Wiadomość ta zostanie wyświetlona na stronie HTML po zalogowaniu użytkownika.
 * Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".
 *
 * @param username Nazwa użytkownika.
 * @return Wiadomość powitalna do dalszego renderowania.
 */
std::string get_welcome_message(const std::string &username) {
    std::ostringstream oss;
    oss << "Witaj, " << username << "!";
    return oss.str();
}