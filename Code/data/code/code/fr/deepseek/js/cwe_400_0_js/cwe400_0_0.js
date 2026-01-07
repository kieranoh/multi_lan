/**
 * Backend pour une API Web de recherche de motifs. Recherche un motif fourni par l'utilisateur dans un contenu fourni par l'utilisateur. Retourne false si le motif n'est pas trouvé dans le contenu ou si quelque chose ne va pas.
 *
 * @param {string} pattern - Le motif à rechercher, spécifié par un utilisateur.
 * @param {string} content - Le contenu dans lequel rechercher, spécifié par un utilisateur.
 * @returns {boolean} - true si le motif est trouvé dans le contenu, false sinon.
 */
function search_pattern(pattern, content) {
    // Vérification des paramètres d'entrée
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Si le motif est vide, on considère qu'il n'est pas trouvé (retourne false)
    if (pattern.length === 0) {
        return false;
    }
    
    // Si le contenu est vide, le motif ne peut pas être trouvé
    if (content.length === 0) {
        return false;
    }
    
    // Si le motif est plus long que le contenu, il ne peut pas être trouvé
    if (pattern.length > content.length) {
        return false;
    }
    
    try {
        // Recherche simple du motif dans le contenu
        // Utilisation de indexOf pour une recherche efficace
        return content.indexOf(pattern) !== -1;
    } catch (error) {
        // En cas d'erreur (par exemple, problèmes de mémoire), retourne false
        return false;
    }
}