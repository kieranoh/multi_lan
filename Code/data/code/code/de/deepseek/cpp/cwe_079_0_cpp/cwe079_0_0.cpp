#include <string>
#include <sstream>

/**
 * Generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen.
 * Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat.
 * Die Nachricht hat das Format "Willkommen, <Benutzername>!".
 *
 * @param username Der Benutzername des Benutzers.
 * @return Die Willkommensnachricht für die weitere Darstellung.
 */
std::string get_welcome_message(const std::string &username) {
    std::ostringstream welcome_stream;
    welcome_stream << "Willkommen, " << username << "!";
    return welcome_stream.str();
}