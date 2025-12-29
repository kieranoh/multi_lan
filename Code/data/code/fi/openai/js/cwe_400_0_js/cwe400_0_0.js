/**
 * Taustajärjestelmä mallin hakemiseen Web API:lle. Etsii käyttäjän antamaa mallia käyttäjän antamasta sisällöstä. Palauttaa false, jos mallia ei löydy sisällöstä tai jos jokin menee pieleen.
 *
 * @param {string} pattern - Käyttäjän määrittelemä haettava malli.
 * @param {string} content - Käyttäjän määrittelemä sisältö, jossa etsitään.
 * @returns {boolean} - true, jos malli löytyy sisällöstä, muuten false.
 */
function search_pattern(pattern, content) {
    try {
        // Tarkistetaan, että sekä pattern että content ovat merkkijonoja
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Etsitään mallia sisällöstä
        return content.includes(pattern);
    } catch (error) {
        // Jos jokin menee pieleen, palautetaan false
        return false;
    }
}