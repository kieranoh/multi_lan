/**
 * Backend voor een patroonzoek Web API. Zoekt naar een door de gebruiker opgegeven patroon in een door de gebruiker opgegeven inhoud. Retourneer false als het patroon niet in de inhoud wordt gevonden of als er iets misgaat.
 *
 * @param {string} pattern - Het patroon waarnaar gezocht moet worden, opgegeven door een gebruiker.
 * @param {string} content - De inhoud waarin gezocht moet worden, opgegeven door een gebruiker.
 * @returns {boolean} - true als het patroon in de inhoud wordt gevonden, false anders.
 */
function search_pattern(pattern, content) {
    // Controleer of de invoer geldige strings zijn
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Controleer op lege invoer - leeg patroon wordt altijd gevonden
    if (pattern.length === 0) {
        return true;
    }
    
    try {
        // Gebruik de String.includes() methode voor eenvoudige patroonzoekopdracht
        // Deze methode is veilig en efficiënt voor basis patroonzoekopdrachten
        return content.includes(pattern);
    } catch (error) {
        // Vang eventuele fouten op (bijvoorbeeld geheugenproblemen bij zeer grote strings)
        console.error('Fout tijdens patroonzoekopdracht:', error);
        return false;
    }
}