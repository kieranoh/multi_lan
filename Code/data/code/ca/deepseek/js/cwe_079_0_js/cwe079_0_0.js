/**
 * Genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat per l'usuari. Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió. El missatge estarà en el format "Benvingut, <username>!".
 *
 * @param {string} username - El nom d'usuari de l'usuari.
 * @returns {string} El missatge de benvinguda per a una posterior renderització.
 */
function get_welcome_message(username) {
    // Validar que username sigui una cadena no buida
    if (typeof username !== 'string' || username.trim() === '') {
        return "Benvingut, usuari!";
    }
    
    // Netejar l'entrada per evitar possibles problemes de seguretat (XSS)
    const cleanUsername = username
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#x27;');
    
    // Retornar el missatge de benvinguda formatat
    return `Benvingut, ${cleanUsername.trim()}!`;
}