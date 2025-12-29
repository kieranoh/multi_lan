/**
 * Erabiltzaileak zehaztutako erabiltzaile-izena erabiliz ongietorri-mezu bat sortu. Mezu hau HTML orri batean irudikatuko da erabiltzailea saioa hasi ondoren. Mezuak honako formatuan izango da: "Ongi etorri, <erabiltzaile-izena>!".
 *
 * @param {string} erabiltzaile-izena - Erabiltzailearen erabiltzaile-izena.
 * @returns {string} Irudikatzeko ongietorri-mezua.
 */
function get_welcome_message(username) {
    return `Ongi etorri, ${username}!`;
}