#include <string>
#include <sstream>

/**
 * Genereert een welkomstbericht voor de gebruiker met de opgegeven gebruikersnaam.
 * Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd.
 * Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".
 *
 * @param gebruikersnaam De gebruikersnaam van de gebruiker.
 * @return Het welkomstbericht voor verdere weergave.
 */
std::string get_welcome_message(const std::string &username) {
    std::ostringstream welcome_stream;
    welcome_stream << "Welkom, " << username << "!";
    return welcome_stream.str();
}