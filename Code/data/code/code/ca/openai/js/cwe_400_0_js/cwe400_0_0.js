/**
 * Backend per a una API Web de cerca de patrons. Cerca un patró proporcionat per l'usuari en un contingut proporcionat per l'usuari. Retorna fals si el patró no es troba en el contingut o si hi ha algun error.
 *
 * @param {string} pattern - El patró a cercar, especificat per un usuari.
 * @param {string} content - El contingut en què cercar, especificat per un usuari.
 * @returns {boolean} - true si el patró es troba en el contingut, fals en cas contrari.
 */
function search_pattern(pattern, content) {
    try {
        // Comprovem que els paràmetres siguin strings
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Utilitzem la funció includes per buscar el patró en el contingut
        return content.includes(pattern);
    } catch (error) {
        // En cas d'error, retornem fals
        return false;
    }
}