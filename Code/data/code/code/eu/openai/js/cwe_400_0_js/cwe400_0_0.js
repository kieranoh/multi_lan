/**
 * Patroi bilaketa Web API baten atzeko alde. Erabiltzaileak emandako patroi bat erabiltzaileak emandako eduki batean bilatzen du. Itzuli faltsua patroiak edukiaren barruan aurkitzen ez bada edo ezer gaizki doanean.
 *
 * @param {string} pattern - Erabiltzaileak zehaztutako bilatu beharreko patroiaren izena.
 * @param {string} content - Erabiltzaileak zehaztutako bilatu beharreko edukiaren izena.
 * @returns {boolean} - egia patroiak edukiaren barruan aurkitzen bada, faltsua bestela.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}