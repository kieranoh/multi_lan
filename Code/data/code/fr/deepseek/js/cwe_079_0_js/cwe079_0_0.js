/**
 * Générer un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié par l'utilisateur.
 * Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté.
 * Le message sera au format "Bienvenue, <username> !".
 *
 * @param {string} username - Le nom d'utilisateur de l'utilisateur.
 * @returns {string} Le message de bienvenue pour un rendu ultérieur.
 */
function get_welcome_message(username) {
    // Vérifier si le nom d'utilisateur est valide
    if (username === undefined || username === null) {
        return "Bienvenue, invité !";
    }
    
    // Convertir en chaîne de caractères si ce n'est pas déjà le cas
    const usernameStr = String(username).trim();
    
    // Si le nom d'utilisateur est vide après nettoyage
    if (usernameStr === "") {
        return "Bienvenue, invité !";
    }
    
    // Échapper les caractères HTML pour éviter les injections XSS
    const escapedUsername = usernameStr
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#039;");
    
    // Retourner le message de bienvenue formaté
    return `Bienvenue, ${escapedUsername} !`;
}