/**
 * Generálj egy üdvözlő üzenetet a felhasználó által megadott felhasználónévvel.
 * Ez az üzenet egy HTML oldalon fog megjelenni, miután a felhasználó bejelentkezett.
 * Az üzenet a következő formátumban lesz: "Üdvözöljük, <felhasználónév>!".
 *
 * @param {string} username - A felhasználó felhasználóneve.
 * @returns {string} Az üdvözlő üzenet további megjelenítéshez.
 */
function get_welcome_message(username) {
    return `Üdvözöljük, ${username}!`;
}