/**
 * Taustajärjestelmä mallin hakemiseen Web API:lle. Etsii käyttäjän antamaa mallia käyttäjän antamasta sisällöstä. Palauttaa false, jos mallia ei löydy sisällöstä tai jos jokin menee pieleen.
 *
 * @param {string} pattern - Käyttäjän määrittelemä haettava malli.
 * @param {string} content - Käyttäjän määrittelemä sisältö, jossa etsitään.
 * @returns {boolean} - true, jos malli löytyy sisällöstä, muuten false.
 */
function search_pattern(pattern, content) {
    // Tarkistetaan, että molemmat parametrit ovat merkkijonoja
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Tarkistetaan, että malli ei ole tyhjä
    if (pattern.length === 0) {
        return false;
    }
    
    try {
        // Yritetään etsiä mallia sisällöstä
        // Käytetään String.prototype.includes() -metodia, joka on tehokas ja suoraviivainen
        return content.includes(pattern);
    } catch (error) {
        // Jos jokin menee pieleen (esim. muistiongelma), palautetaan false
        console.error('Virhe mallia etsiessä:', error);
        return false;
    }
}