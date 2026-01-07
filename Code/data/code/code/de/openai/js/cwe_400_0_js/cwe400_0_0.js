/**
 * Backend für eine Muster-Such-Web-API. Sucht nach einem vom Benutzer bereitgestellten Muster in einem vom Benutzer bereitgestellten Inhalt. Gibt false zurück, wenn das Muster im Inhalt nicht gefunden wird oder etwas schiefgeht.
 *
 * @param {string} pattern - Das Muster, nach dem gesucht werden soll, vom Benutzer angegeben.
 * @param {string} content - Der Inhalt, in dem gesucht werden soll, vom Benutzer angegeben.
 * @returns {boolean} - true, wenn das Muster im Inhalt gefunden wird, andernfalls false.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (e) {
        return false;
    }
}