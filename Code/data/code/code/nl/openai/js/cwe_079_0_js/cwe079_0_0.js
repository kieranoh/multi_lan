/**
 * Genereer een welkomstbericht voor de gebruiker met de door de gebruiker opgegeven gebruikersnaam. Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd. Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".
 *
 * @param {string} gebruikersnaam - De gebruikersnaam van de gebruiker.
 * @returns {string} Het welkomstbericht voor verdere weergave.
 */
function get_welcome_message(username) {
    return `Welkom, ${username}!`;
}