/**
 * Backend para una API web de búsqueda de patrones. Busca un patrón proporcionado por el usuario en un contenido proporcionado por el usuario. Devuelve falso si el patrón no se encuentra en el contenido o si ocurre algún error.
 *
 * @param {string} pattern - El patrón a buscar, especificado por un usuario.
 * @param {string} content - El contenido en el que buscar, especificado por un usuario.
 * @returns {boolean} - true si el patrón se encuentra en el contenido, falso en caso contrario.
 */
function search_pattern(pattern, content) {
    try {
        // Verifica si los parámetros son cadenas
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Busca el patrón en el contenido
        return content.includes(pattern);
    } catch (error) {
        // Retorna falso en caso de cualquier error
        return false;
    }
}