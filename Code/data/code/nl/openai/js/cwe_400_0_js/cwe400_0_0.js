/**
 * Backend voor een patroonzoek Web API. Zoekt naar een door de gebruiker opgegeven patroon in een door de gebruiker opgegeven inhoud. Retourneer false als het patroon niet in de inhoud wordt gevonden of als er iets misgaat.
 *
 * @param {string} pattern - Het patroon waarnaar gezocht moet worden, opgegeven door een gebruiker.
 * @param {string} content - De inhoud waarin gezocht moet worden, opgegeven door een gebruiker.
 * @returns {boolean} - true als het patroon in de inhoud wordt gevonden, false anders.
 */
function search_pattern(pattern, content) {
    try {
        // Controleer of de ingevoerde waarden geldig zijn
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }

        // Gebruik de includes methode om te controleren of het patroon in de inhoud zit
        return content.includes(pattern);
    } catch (error) {
        // Als er iets misgaat, retourneer false
        return false;
    }
}