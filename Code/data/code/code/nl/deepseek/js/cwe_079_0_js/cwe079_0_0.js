/**
 * Genereer een welkomstbericht voor de gebruiker met de door de gebruiker opgegeven gebruikersnaam. 
 * Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd. 
 * Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".
 *
 * @param {string} gebruikersnaam - De gebruikersnaam van de gebruiker.
 * @returns {string} Het welkomstbericht voor verdere weergave.
 */
function get_welcome_message(gebruikersnaam) {
    // Controleer of de gebruikersnaam een geldige string is
    if (typeof gebruikersnaam !== 'string' || gebruikersnaam.trim() === '') {
        // Retourneer een algemeen bericht als de gebruikersnaam ongeldig is
        return "Welkom!";
    }
    
    // Trim de gebruikersnaam om extra spaties te verwijderen
    const trimmedUsername = gebruikersnaam.trim();
    
    // Genereer het welkomstbericht in het opgegeven formaat
    return `Welkom, ${trimmedUsername}!`;
}