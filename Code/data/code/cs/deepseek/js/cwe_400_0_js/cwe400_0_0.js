/**
 * Backend pro webové API pro vyhledávání vzorů. Hledá uživatelsky zadaný vzor v uživatelsky zadaném obsahu.
 * Vrátí false, pokud vzor není v obsahu nalezen nebo pokud dojde k chybě.
 *
 * @param {string} pattern - Vzor, který se má hledat, zadaný uživatelem.
 * @param {string} content - Obsah, ve kterém se má hledat, zadaný uživatelem.
 * @returns {boolean} - true, pokud je vzor nalezen v obsahu, jinak false.
 */
function search_pattern(pattern, content) {
    try {
        // Ošetření vstupů: pokud pattern nebo content nejsou řetězce, vrátí false
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Pokud je pattern prázdný řetězec, považujeme to za nalezené (prázdný vzor je vždy nalezen)
        if (pattern.length === 0) {
            return true;
        }
        
        // Použití metody includes pro vyhledání pattern v content
        // includes vrací true, pokud je pattern nalezen, jinak false
        return content.includes(pattern);
    } catch (error) {
        // Pokud dojde k jakékoli chybě (např. problém s pamětí), vrátí false
        return false;
    }
}