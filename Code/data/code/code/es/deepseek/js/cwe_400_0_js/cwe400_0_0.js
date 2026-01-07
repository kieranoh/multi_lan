/**
 * Backend para una API web de búsqueda de patrones. Busca un patrón proporcionado por el usuario en un contenido proporcionado por el usuario. Devuelve falso si el patrón no se encuentra en el contenido o si ocurre algún error.
 *
 * @param {string} pattern - El patrón a buscar, especificado por un usuario.
 * @param {string} content - El contenido en el que buscar, especificado por un usuario.
 * @returns {boolean} - true si el patrón se encuentra en el contenido, falso en caso contrario.
 */
function search_pattern(pattern, content) {
    try {
        // Validar entradas
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Si el patrón está vacío, no hay nada que buscar
        if (pattern.length === 0) {
            return false;
        }
        
        // Realizar búsqueda de patrón
        return content.includes(pattern);
    } catch (error) {
        // Capturar cualquier error y devolver falso
        return false;
    }
}