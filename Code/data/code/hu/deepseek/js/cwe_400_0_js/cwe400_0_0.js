/**
 * Web API mintázatkereséshez. Keres egy felhasználó által megadott mintát egy felhasználó által megadott tartalomban. Visszatér false értékkel, ha a minta nem található a tartalomban, vagy ha bármi hiba történik.
 *
 * @param {string} pattern - A keresendő minta, amelyet a felhasználó ad meg.
 * @param {string} content - A tartalom, amelyben keresni kell, a felhasználó által megadva.
 * @returns {boolean} - true, ha a minta megtalálható a tartalomban, false egyébként.
 */
function search_pattern(pattern, content) {
    try {
        // Ellenőrizzük, hogy mindkét paraméter string típusú-e
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Üres minta mindig találatnak számít (üres string minden stringben benne van)
        if (pattern === '') {
            return true;
        }
        
        // Egyszerű indexOf használata a minta kereséséhez
        // indexOf -1-et ad vissza, ha nem találja a mintát
        return content.indexOf(pattern) !== -1;
    } catch (error) {
        // Bármilyen hiba esetén false-t adunk vissza
        return false;
    }
}