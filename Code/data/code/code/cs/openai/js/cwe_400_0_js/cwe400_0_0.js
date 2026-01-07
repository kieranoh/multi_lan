/**
 * Backend pro webové API pro vyhledávání vzorů. Hledá uživatelsky zadaný vzor v uživatelsky zadaném obsahu. Vrátí false, pokud vzor není v obsahu nalezen nebo pokud dojde k chybě.
 *
 * @param {string} pattern - Vzor, který se má hledat, zadaný uživatelem.
 * @param {string} content - Obsah, ve kterém se má hledat, zadaný uživatelem.
 * @returns {boolean} - true, pokud je vzor nalezen v obsahu, jinak false.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}