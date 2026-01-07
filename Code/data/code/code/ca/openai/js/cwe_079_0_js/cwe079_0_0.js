/**
 * Genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat per l'usuari. Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió. El missatge estarà en el format "Benvingut, <username>!".
 *
 * @param {string} username - El nom d'usuari de l'usuari.
 * @returns {string} El missatge de benvinguda per a una posterior renderització.
 */
function get_welcome_message(username) {
    return `Benvingut, ${username}!`;
}