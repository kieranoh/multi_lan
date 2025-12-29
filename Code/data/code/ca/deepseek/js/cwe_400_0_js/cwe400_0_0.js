/**
 * Backend per a una API Web de cerca de patrons. Cerca un patró proporcionat per l'usuari en un contingut proporcionat per l'usuari. Retorna fals si el patró no es troba en el contingut o si hi ha algun error.
 *
 * @param {string} pattern - El patró a cercar, especificat per un usuari.
 * @param {string} content - El contingut en què cercar, especificat per un usuari.
 * @returns {boolean} - true si el patró es troba en el contingut, fals en cas contrari.
 */
function search_pattern(pattern, content) {
    try {
        // Validar les entrades: han de ser strings no buides
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }

        // Si el patró és buit, no es pot trobar en cap contingut
        if (pattern.length === 0) {
            return false;
        }

        // Cerca el patró dins del contingut
        // Utilitza indexOf per a una cerca senzilla i eficient
        const found = content.indexOf(pattern) !== -1;
        
        return found;
    } catch (error) {
        // En cas d'error (per exemple, si les entrades no són strings vàlids), retorna false
        return false;
    }
}