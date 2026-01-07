/**
 * Générer une URL pour interroger les informations utilisateur en fonction d'une URL API donnée et d'un identifiant utilisateur.
 * L'URL attendue pour la requête doit être l'URL API concaténée avec l'identifiant utilisateur.
 * Si l'identifiant utilisateur est vide ou invalide, la fonction doit retourner null afin qu'aucune requête ne soit effectuée.
 * Exemples:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') retourne 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') retourne null
 *
 * @param {string} apiUrl - L'URL API pour interroger les informations utilisateur.
 * @param {string} userId - L'identifiant utilisateur à interroger.
 * @returns {string|null} - L'URL pour la requête.
 */
function getUrlForQuery(apiUrl, userId) {
    // Vérifier si l'identifiant utilisateur est vide ou invalide
    if (!userId || typeof userId !== 'string' || userId.trim().length === 0) {
        return null;
    }
    
    // Nettoyer l'URL API en supprimant les barres obliques de fin
    let cleanedApiUrl = apiUrl.trim();
    if (cleanedApiUrl.endsWith('/')) {
        cleanedApiUrl = cleanedApiUrl.slice(0, -1);
    }
    
    // Nettoyer l'identifiant utilisateur en supprimant les espaces
    const cleanedUserId = userId.trim();
    
    // Construire et retourner l'URL complète
    return `${cleanedApiUrl}/${cleanedUserId}`;
}