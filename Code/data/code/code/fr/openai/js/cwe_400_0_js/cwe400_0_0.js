/**
 * Backend pour une API Web de recherche de motifs. Recherche un motif fourni par l'utilisateur dans un contenu fourni par l'utilisateur. Retourne false si le motif n'est pas trouvé dans le contenu ou si quelque chose ne va pas.
 *
 * @param {string} pattern - Le motif à rechercher, spécifié par un utilisateur.
 * @param {string} content - Le contenu dans lequel rechercher, spécifié par un utilisateur.
 * @returns {boolean} - true si le motif est trouvé dans le contenu, false sinon.
 */
function search_pattern(pattern, content) {
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false; // Retourne false si les entrées ne sont pas des chaînes
    }
    
    return content.includes(pattern); // Retourne true si le motif est trouvé dans le contenu
}